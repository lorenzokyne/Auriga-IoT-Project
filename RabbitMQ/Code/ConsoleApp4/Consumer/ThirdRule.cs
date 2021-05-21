using Consumer.Observables;
using Consumer.Observers;
using RabbitMQ.Client;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class ThirdRule
    {

        public ThirdRule(IObservable<bool> motionObservable, IObservable<float> temperatureObservable)
        {
            TemperatureObserver temperature = new TemperatureObserver();
            MotionObserver motion = new MotionObserver();

            motionObservable.Subscribe(motion);
            temperatureObservable.Subscribe(temperature);
            new Task(() =>
            {
                while (true)
                {
                    if (motion.Value == true && temperature.Value > 60 )
                    {
                        Console.WriteLine("Third Rule verified!");
                        string message = "Stacca stacca!";
                        new Producer.Producer(message);
                        motion.Value = false;
                        temperature.Value = 0;
                    }
                    //else
                    //{
                    //    new Producer.Producer("Apri tutto");
                    //}
                    Thread.Sleep(5000);
                }
            }).Start();
        }

    }
}
