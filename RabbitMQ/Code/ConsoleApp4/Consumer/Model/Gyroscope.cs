using System;

namespace Consumer.Model
{
    public class Gyroscope
    {
        private int gyX;
        private int gyY;
        private int gyZ;

        private int acX;
        private int acY;
        private int acZ;

        public int GyX { get => gyX; set => gyX = value; }
        public int GyY { get => gyY; set => gyY = value; }
        public int GyZ { get => gyZ; set => gyZ = value; }
        public int AcX { get => acX; set => acX = value; }
        public int AcY { get => acY; set => acY = value; }
        public int AcZ { get => acZ; set => acZ = value; }

        public Gyroscope(int gyX, int gyZ, int gyY, int acX, int acY, int acZ)
        {
            this.gyX = gyX;
            this.gyY = gyY;
            this.gyZ = gyZ;

            this.acX = acX;
            this.acY = acY;
            this.acZ = acZ;
        }

        public override String ToString()
        {
            return String.Format("GyX: {0} - GyY: {1} - GyZ: {2} | AcX: {3} - AcY: {4} - AcZ: {5}", gyX, gyY, gyZ, acX, acY, acZ);
        }
    }
}
