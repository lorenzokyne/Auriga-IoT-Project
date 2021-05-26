using RabbitMQ.Client;
using System;

namespace Consumer
{
    public class AtmLogic
    {
        public static void Main(String[] args)
        {
            var factory = new ConnectionFactory() { HostName = "192.168.30.13", UserName = "atm", Password = "atm" };
            using (var connection = factory.CreateConnection())
            using (FirstScenarioLogic scenario1 = new FirstScenarioLogic(connection))
            using (SecondScenarioLogic scenario2 = new SecondScenarioLogic(connection))
                Console.ReadLine();

        }
    }
}
