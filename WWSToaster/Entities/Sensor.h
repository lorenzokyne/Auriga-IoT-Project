
class Sensor {
    private:
        char* topic;
        char* value = "";
    public:
        Sensor(char* topicValue){
            topic = topicValue;
        };
        virtual void setValue();
        virtual char* getValue();
};