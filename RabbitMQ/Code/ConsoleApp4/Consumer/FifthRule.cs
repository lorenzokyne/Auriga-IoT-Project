using Consumer.Observers;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class FifthRule
    {

        public FifthRule(IObservable<int> jammerSensor)
        {
            NoiseObserver jammer = new NoiseObserver();
            MotionObserver motion = new MotionObserver();
            
            jammerSensor.Subscribe(jammer);
            new Task(() =>
            {
                while (true)
                {
                    if (jammer.Value < 400 || jammer.Value > 600)
                    {
                        Console.WriteLine("Second Rule verified!");
                        string message = "Stacca stacca!";
                        message = message.Length.ToString().PadLeft(2, '0') + message;
                        new Producer.Producer(message);
                        jammer.Value = 500;
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
