using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Consumer.Observers
{
    public class TemperatureObserver : IObserver<float>
    {
        private IDisposable unsubscriber;
        private float value;

        public float Value { get => value; set => this.value = value; }

        public virtual void OnCompleted()
        {
            this.Unsubscribe();
        }

        public virtual void OnError(Exception e)
        {
        }

        public virtual void OnNext(float value)
        {
            this.Value = value;
            Console.WriteLine("The current temperature is {0}", value);
        }

        public virtual void Unsubscribe()
        {
            unsubscriber.Dispose();
        }
    }
}
