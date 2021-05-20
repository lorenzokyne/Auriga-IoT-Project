using Consumer.Observables;
using RabbitMQ.Client;
using System;

namespace Consumer
{
    class FirstScenarioLogic
    {
        static void Main(string[] args)
        {
            var factory = new ConnectionFactory() { HostName = "192.168.30.13", UserName = "atm", Password = "atm" };

            using (var connection = factory.CreateConnection())
            using (var brightChannel = connection.CreateModel())
            using (var tempChannel = connection.CreateModel())
            using (var noiseChannel = connection.CreateModel())
            using (var motionChannel = connection.CreateModel())
            using (var jammerChannel = connection.CreateModel())
            {
                TemperatureObservable tempobservable = new TemperatureObservable(tempChannel);
                BrightnessObservable brighobservable = new BrightnessObservable(brightChannel);
                NoiseObservable noiseObservable = new NoiseObservable(noiseChannel);
                MotionObservable motionObservable = new MotionObservable(motionChannel);
                JammerObservable jammerObservable = new JammerObservable(jammerChannel);
                FirstRule rule1 = new FirstRule(tempobservable, brighobservable);
                SecondRule rule2 = new SecondRule(noiseObservable, brighobservable);
                ThirdRule rule3 = new ThirdRule(motionObservable, tempobservable);
                FourthRule rule4 = new FourthRule(motionObservable, noiseObservable);
                FifthRule rule5 = new FifthRule(jammerObservable);
                Console.ReadLine();
            }


        }
    }
}
