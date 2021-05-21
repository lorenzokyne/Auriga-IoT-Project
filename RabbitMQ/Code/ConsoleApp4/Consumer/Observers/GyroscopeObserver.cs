using Consumer.Model;
using System;

namespace Consumer.Observers
{
    public class GyroscopeObserver : IObserver<Gyroscope>
    {
        private IDisposable unsubscriber;
        private Gyroscope value;

        public Gyroscope Value { get => value; set => this.value = value; }

        public virtual void Subscribe(IObservable<Gyroscope> provider)
        {
            if (provider != null)
                unsubscriber = provider.Subscribe(this);
        }

        public virtual void OnCompleted()
        {
            this.Unsubscribe();
        }

        public virtual void OnError(Exception e)
        {
        }

        public virtual void OnNext(Gyroscope value)
        {
            this.Value = value;
            Console.WriteLine("The current gyroscope value is: {0}", value.ToString());
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
    }
}
