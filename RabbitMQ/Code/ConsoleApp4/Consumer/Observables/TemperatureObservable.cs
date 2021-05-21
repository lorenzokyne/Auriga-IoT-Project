using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace Consumer.Observables
{
    public class TemperatureObservable : IObservable<float>
    {
        private List<IObserver<float>> observers;
        public TemperatureObservable(IModel channel)
        {

            channel.BasicQos(prefetchSize: 0, prefetchCount: 1, global: false);

            Console.WriteLine("Waiting for messages...");

            var consumer = new EventingBasicConsumer(channel);
            consumer.Received += (sender, ea) =>
            {
                var body = ea.Body.ToArray();
                var message = Encoding.UTF8.GetString(body);
                Console.WriteLine("Received: {0}", message);
                float value = float.Parse(message.Split(':')[1].Split(',')[0], NumberStyles.Any, CultureInfo.InvariantCulture);
                this.UpdateValue(value);
                Console.WriteLine("Done");
                channel.BasicAck(deliveryTag: ea.DeliveryTag, multiple: false);
            };
            channel.BasicConsume(queue: "q_temp-humidity",
                                 autoAck: false,
                                 consumer: consumer);

            observers = new List<IObserver<float>>();
        }

        public IDisposable Subscribe(IObserver<float> observer)
        {
            if (!observers.Contains(observer))
                observers.Add(observer);
            return new Unsubscriber(observers, observer);
        }

        private class Unsubscriber : IDisposable
        {
            private List<IObserver<float>> _observers;
            private IObserver<float> _observer;

            public Unsubscriber(List<IObserver<float>> observers, IObserver<float> observer)
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
        public void UpdateValue(Nullable<float> val)
        {
            foreach (var observer in observers)
            {
                if (!val.HasValue)
                    observer.OnError(new Exception());
                else
                    observer.OnNext(val.Value);
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
