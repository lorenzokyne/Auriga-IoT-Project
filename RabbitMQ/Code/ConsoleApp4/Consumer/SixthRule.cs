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
                    if (gps.Value.Item1!= 0 || gps.Value.Item2 != 0)
                    {
                        Console.WriteLine("Sixth Rule verified!");
                        string message = "send gps";
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
        }
    }
}
