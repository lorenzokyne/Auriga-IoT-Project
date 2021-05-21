using Consumer.Observables;
using Consumer.Observers;
using RabbitMQ.Client;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{
    class FirstRule
    {
        public FirstRule(IObservable<float> tempobservable, IObservable<int> brighobservable)
        {            
            TemperatureObserver temperature = new TemperatureObserver();
            BrightnessObserver brightness = new BrightnessObserver();

            tempobservable.Subscribe(temperature);
            brighobservable.Subscribe(brightness);
            new Task(() =>
            {
                while (true)
                {
                    if (temperature.Value > 59.00f && (brightness.Value > 0 && brightness.Value < 200))
                    {
                        Console.WriteLine("First Rule verified!");
                        string message = "Stacca stacca!";
                        message = message.Length.ToString().PadLeft(2, '0') + message;
                        new Producer.Producer(message);
                        temperature.Value = 0;
                        brightness.Value = 0;
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
