using RabbitMQ.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Producer
{
    public class Producer
    {
        public Producer(string message)
        {
            var factory = new ConnectionFactory() { HostName = "192.168.30.13", UserName = "atm", Password = "atm" };
            using (var connection = factory.CreateConnection())
            using (var channel = connection.CreateModel())
            {


                //var message = "Apri tutto";
                message = message.Length.ToString().PadLeft(2, '0') + message;
                var body = Encoding.UTF8.GetBytes(message);

                var properties = channel.CreateBasicProperties();
                properties.Persistent = true;

                channel.BasicPublish(exchange: "amq.topic",
                                     routingKey: "WWSToaster-00",
                                     basicProperties: properties,
                                     body: body);
                Console.WriteLine("Sent: {0}", message);
            }
        }
    }
}
