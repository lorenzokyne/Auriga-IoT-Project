using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace Consumer.Observables
{
    public class GpsObservable : IObservable<Tuple<float, float>>
    {
        private List<IObserver<Tuple<float, float>>> observers;
        public GpsObservable(IModel channel)
        {
            channel.BasicQos(prefetchSize: 0, prefetchCount: 1, global: false);

            Console.WriteLine("Waiting for messages...");

            var consumer = new EventingBasicConsumer(channel);
            consumer.Received += (sender, ea) =>
            {
                var body = ea.Body.ToArray();
                var message = Encoding.UTF8.GetString(body);
                Console.WriteLine("Received: {0}", message);
                string[] gpsValues = message.Split(';');
                float lat = float.Parse(gpsValues[0].Split(':')[2],NumberStyles.Any, CultureInfo.InvariantCulture);
                float lon = float.Parse(gpsValues[1].Split(':')[1], NumberStyles.Any, CultureInfo.InvariantCulture);
                this.UpdateValue(new Tuple<float, float>(lat,lon));
                Console.WriteLine("Done");

                // Note: it is possible to access the channel via
                //       ((EventingBasicConsumer)sender).Model here
                channel.BasicAck(deliveryTag: ea.DeliveryTag, multiple: false);
            };
            channel.BasicConsume(queue: "q_gps",
                                 autoAck: false,
                                 consumer: consumer);
            observers = new List<IObserver<Tuple<float, float>>>();
        }

        public IDisposable Subscribe(IObserver<Tuple<float, float>> observer)
        {
            if (!observers.Contains(observer))
                observers.Add(observer);
            return new Unsubscriber(observers, observer);
        }

        private class Unsubscriber : IDisposable
        {
            private List<IObserver<Tuple<float, float>>> _observers;
            private IObserver<Tuple<float, float>> _observer;

            public Unsubscriber(List<IObserver<Tuple<float, float>>> observers, IObserver<Tuple<float, float>> observer)
            {
                this._observers = observers;
                this._observer = observer;
            }

            public void Dispose()
            {
                if (_observer != null && _observers.Contains(_observer))
                    _observers.Remove(_observer);
            }
        }
        private void UpdateValue(Tuple<float, float> val)
        {
            foreach (var observer in observers)
            {
                    observer.OnNext(val);
            }
        }

        public void EndTransmission()
        {
            foreach (var observer in observers.ToArray())
                if (observers.Contains(observer))
                    observer.OnCompleted();

            observers.Clear();
        }
    }
}
