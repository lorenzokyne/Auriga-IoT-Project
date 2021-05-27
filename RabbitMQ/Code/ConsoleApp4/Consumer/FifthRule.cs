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
            JammerObserver jammer = new JammerObserver();
            MotionObserver motion = new MotionObserver();
            
            jammerSensor.Subscribe(jammer);
            new Task(() =>
            {
                while (true)
                {
                    if (jammer.Value>0 && (jammer.Value < 400 || jammer.Value > 600))
                    {
                        Console.WriteLine("Fifth Rule verified!");
                        string message = "Stacca stacca!";
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
