
// Structure to hold the timestamp value
struct Time
{
    int day;
    int month;
    int hour;
};

// Structure to hold the data fields of a storm
struct Data
{
    float latitude;
    float longitude;
    struct Time timestamp;
    int wind_speed;
    int pressure;
    char *storm_type;
    struct Data *next;
    struct Data *previous;
};

// Structure to hold the list of storms
struct Storm
{
    char *name;
    struct Storm *next;
    struct Storm *previous;
    struct Data *data;
};

