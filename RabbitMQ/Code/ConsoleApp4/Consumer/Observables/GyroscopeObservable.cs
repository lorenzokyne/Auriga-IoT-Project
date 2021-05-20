using Consumer.Model;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System;
using System.Collections.Generic;
using System.Text;

namespace Consumer.Observables
{
    class GyroscopeObservable : IObservable<Gyroscope>
    {
        private List<IObserver<Gyroscope>> observers;
        public GyroscopeObservable(IModel channel)
        {
            channel.BasicQos(prefetchSize: 0, prefetchCount: 1, global: false);

            Console.WriteLine("Waiting for messages...");

            var consumer = new EventingBasicConsumer(channel);
            consumer.Received += (sender, ea) =>
            {
                var body = ea.Body.ToArray();
                var message = Encoding.UTF8.GetString(body);
                Console.WriteLine("Received: {0}", message);
                string gyroscopeValues = message.Split(':')[1];
                int gyX = int.Parse(gyroscopeValues.Split(';')[0].Split('=')[1]);
                int gyY = int.Parse(gyroscopeValues.Split(';')[1].Split('=')[1]);
                int gyZ = int.Parse(gyroscopeValues.Split(';')[2].Split('=')[1]);
                int acX = int.Parse(gyroscopeValues.Split(';')[3].Split('=')[1]);
                int acY = int.Parse(gyroscopeValues.Split(';')[4].Split('=')[1]);
                int acZ = int.Parse(gyroscopeValues.Split(';')[5].Split('=')[1]);
                this.UpdateValue(new Gyroscope(gyX, gyZ, gyY, acX, acY, acZ));
                Console.WriteLine("Done");

                // Note: it is possible to access the channel via
                //       ((EventingBasicConsumer)sender).Model here
                channel.BasicAck(deliveryTag: ea.DeliveryTag, multiple: false);
            };
            channel.BasicConsume(queue: "q_gyroscope",
                                 autoAck: false,
                                 consumer: consumer);
            observers = new List<IObserver<Gyroscope>>();
        }

        public IDisposable Subscribe(IObserver<Gyroscope> observer)
        {
            if (!observers.Contains(observer))
                observers.Add(observer);
            return new Unsubscriber(observers, observer);
        }

        private class Unsubscriber : IDisposable
        {
            private List<IObserver<Gyroscope>> _observers;
            private IObserver<Gyroscope> _observer;

            public Unsubscriber(List<IObserver<Gyroscope>> observers, IObserver<Gyroscope> observer)
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
        private void UpdateValue(Gyroscope val)
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
