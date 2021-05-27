using Consumer.Model;
using Consumer.Observers;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Consumer
{

    class SeventhRule
    {
        public SeventhRule(IObservable<Gyroscope> gyroscopeSensor)
        {
            GyroscopeObserver gyroscope = new GyroscopeObserver();

            gyroscopeSensor.Subscribe(gyroscope);
            new Task(() =>
            {
                while (true)
                {
                    if (gyroscope.Value !=null && (gyroscope.Value.GyX>10000 || gyroscope.Value.GyY > 10000||gyroscope.Value.GyZ > 10000) || (gyroscope.Value.GyX < -10000 || gyroscope.Value.GyY < -10000 || gyroscope.Value.GyZ < -10000))
                    {
                        Console.WriteLine("Seventh Rule verified!");
                        string message = "send gps";
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
