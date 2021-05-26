using Consumer.Observers;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class SixthRule
    {

        public SixthRule(IObservable<Tuple<float,float>> gpsSensor)
        {
            GpsObserver gps = new GpsObserver();

            gpsSensor.Subscribe(gps);
            new Task(() =>
            {
                while (true)
                {
                    if ((gps.Value != null) && (gps.Value.Item1!= 0 || gps.Value.Item2 != 0) && (gps.Value.Item1 != 1000 && gps.Value.Item2 != 1000))
                    {
                        Console.WriteLine("Sixth Rule verified!");
                        string message = "send gps";
                        new Producer.Producer(message);
                    }
                    Thread.Sleep(5000);
                }
            }).Start();
        }
    }
}
