using Consumer.Observers;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class FourthScenario
    {

        public FourthScenario(IObservable<bool> motionObservable, IObservable<int> noisebservable)
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
