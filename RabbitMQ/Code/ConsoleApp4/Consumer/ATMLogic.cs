using Consumer.Observables;
using RabbitMQ.Client;
using System;

namespace Consumer
{
    class ATMLogic
    {
        static void Main(string[] args)
        {
            var factory = new ConnectionFactory() { HostName = "192.168.30.13", UserName = "atm", Password = "atm" };

            using (var connection = factory.CreateConnection())
            using (var brightChannel = connection.CreateModel())
            using (var tempChannel = connection.CreateModel())
            using (var noiseChannel = connection.CreateModel())
            using (var motionChannel = connection.CreateModel())
            {
                TemperatureObservable tempobservable = new TemperatureObservable(tempChannel);
                BrightnessObservable brighobservable = new BrightnessObservable(brightChannel);
                NoiseObservable noiseObservable = new NoiseObservable(noiseChannel);
                MotionObservable motionObservable = new MotionObservable(motionChannel);
                FirstScenario scenario1 = new FirstScenario(tempobservable, brighobservable);
                SecondScenario scenario2 = new SecondScenario(noiseObservable, brighobservable);
                ThirdScenario scenario3 = new ThirdScenario(motionObservable, tempobservable);
                FourthScenario scenario4 = new FourthScenario(motionObservable, noiseObservable);
                Console.ReadLine();
            }


        }
    }
}
