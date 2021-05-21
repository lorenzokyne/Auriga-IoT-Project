using Consumer.Observers;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class FourthRule
    {

        public FourthRule(IObservable<bool> motionObservable, IObservable<int> noisebservable)
        {
            NoiseObserver noise = new NoiseObserver();
            MotionObserver motion = new MotionObserver();

            motionObservable.Subscribe(motion);
            noisebservable.Subscribe(noise);
            new Task(() =>
            {
                while (true)
                {
                    if (motion.Value == true && noise.Value < 500)
                    {
                        Console.WriteLine("Fourth Rule verified!");
                        string message = "Stacca stacca!";
                        new Producer.Producer(message);
                        motion.Value = false;
                        noise.Value = 0;
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
