using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Consumer.Observers
{
    public class NoiseObserver : IObserver<int>
    {
        private IDisposable unsubscriber;
        private int value;

        public int Value { get => value; set => this.value = value; }

        public virtual void Subscribe(IObservable<int> provider)
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

        public virtual void OnNext(int value)
        {
            this.Value = value;
            Console.WriteLine("The current noise value is {0}", value);
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
    }
}
