using Consumer.Observables;
using Consumer.Observers;
using RabbitMQ.Client;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class ThirdScenario
    {

        public ThirdScenario(IObservable<bool> motionObservable, IObservable<float> temperatureObservable)
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
                        string message = "Stacca stacca!";
                        message = message.Length.ToString().PadLeft(2, '0') + message;
                        new Producer.Producer(message);
                    }
                    //else
                    //{
                    //    new Producer.Producer("Apri tutto");
                    //}
                    Thread.Sleep(5000);
                }
            }).Start();
            Console.ReadLine();
        }

    }
}
