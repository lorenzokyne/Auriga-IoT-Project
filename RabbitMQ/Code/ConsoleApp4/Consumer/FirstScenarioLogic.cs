using Consumer.Observables;
using RabbitMQ.Client;
using System;

namespace Consumer
{
    class FirstScenarioLogic : IDisposable
    {
        private IModel brightChannel;
        private IModel tempChannel;
        private IModel noiseChannel;
        private IModel motionChannel;
        private IModel jammerChannel;
        public FirstScenarioLogic(IConnection connection)
        {
            brightChannel = connection.CreateModel();
            tempChannel = connection.CreateModel();
            noiseChannel = connection.CreateModel();
            motionChannel = connection.CreateModel();
            jammerChannel = connection.CreateModel();
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

        }
        public void Dispose()
        {
            brightChannel.Dispose();
            tempChannel.Dispose();
            noiseChannel.Dispose();
            motionChannel.Dispose();
            jammerChannel.Dispose();
        }
    }
}
