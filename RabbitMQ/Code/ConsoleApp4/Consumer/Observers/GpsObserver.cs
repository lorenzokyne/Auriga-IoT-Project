using System;

namespace Consumer.Observers
{
    public class GpsObserver : IObserver<Tuple<float, float>>
    {
        private IDisposable unsubscriber;
        private Tuple<float, float> value;

        public Tuple<float, float> Value { get => value; set => this.value = value; }

        public virtual void Subscribe(IObservable<Tuple<float, float>> provider)
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

        public virtual void OnNext(Tuple<float, float> value)
        {
            this.Value = value;
            Console.WriteLine("The current gps position is Lat:{0}, Lon:{1}", value.Item1, value.Item2);
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
    }
}
