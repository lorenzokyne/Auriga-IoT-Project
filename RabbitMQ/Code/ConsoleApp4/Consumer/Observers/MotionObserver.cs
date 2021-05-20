using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Consumer.Observers
{
    public class MotionObserver : IObserver<bool>
    {
        private IDisposable unsubscriber;
        private bool value;

        public bool Value { get => value; set => this.value = value; }

        public virtual void Subscribe(IObservable<bool> provider)
        {
            if (provider != null)
                unsubscriber = provider.Subscribe(this);
        }

        public virtual void OnCompleted()
        {
            Console.WriteLine("The Location Tracker has completed transmitting data to.");
            this.Unsubscribe();
        }

        public virtual void OnError(Exception e)
        {
            Console.WriteLine("The location cannot be determined.");
        }

        public virtual void OnNext(bool value)
        {
            this.Value = value;
            Console.WriteLine("Movement detected: {0}", value);
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
    }
}
