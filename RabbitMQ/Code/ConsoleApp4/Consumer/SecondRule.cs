using Consumer.Observables;
using Consumer.Observers;
using RabbitMQ.Client;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class SecondRule
    {

        public SecondRule(IObservable<int> noisebservable, IObservable<int> brighobservable)
        {
            NoiseObserver noise = new NoiseObserver();
            BrightnessObserver brightness = new BrightnessObserver();

            noisebservable.Subscribe(noise);
            brighobservable.Subscribe(brightness);
            new Task(() =>
            {
                while (true)
                {
                    if (noise.Value > 0 && noise.Value < 500 && brightness.Value > 0 && brightness.Value < 400)
                    {
                        Console.WriteLine("Second Rule verified!");
                        string message = "Stacca stacca!";
                        new Producer.Producer(message);
                        noise.Value = 0;
                        brightness.Value = 0;
                    }
                    Thread.Sleep(5000);
                }
            }).Start();
        }
    
    }
}
