#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;


// Define a class with name Date to store a date with
class Date
{
private:
    short unsigned int day;
    short unsigned int month;
    short unsigned int year;

    // a public overloaded constructor to initialise a date.

public:
    Date(short unsigned int d = 0, short unsigned int m = 0, short unsigned int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }

    Date operator+(int n)
    {
        int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int newDay = day + n;
        int newMonth = month;
        int newYear = year;

        while (newDay > daysInMonth[newMonth - 1])
        {
            newDay -= daysInMonth[newMonth - 1];
            newMonth++;
            if (newMonth > 12)
            {
                newMonth = 1;
                newYear++;
            }
        }

        return Date(newDay, newMonth, newYear);
    }

    // an overloaded friend input and output operator, where a date in above shown ISO-8601 date format shall be read and written respectively.
    friend ostream& operator<<(ostream& output, const Date& D)
    {
        output << D.year << "-" << setfill('0') << setw(2) << D.month << "-" << setfill('0') << setw(2) << D.day;
        return output;
    }

    friend istream& operator>>(istream& input, Date& D)
    {
        input >> D.year;
        input.ignore();
        input >> D.month;
        input.ignore();
        input >> D.day;
        return input;
    }
};





// Define an abstract class with name Transport with following members:
class Transport
{
    // a public virtual destructor writing an output message like in the examples below.
public:
    virtual ~Transport()
    {
        cout << "destructor Transport done" << endl;
    }

    // a public virtual member function with name includedTransfer without parameter and a Boolen return value. In its body always value false
    // shall be returned
    virtual bool includedTransfer() const
    {
        return false;
    }

    // a public abstract/pure virtual member function with name get_price without parameter and a real-valued return.
    virtual double get_price() const = 0;

    // a public abstract/pure virtual member function with name print without parameter or return value.
    virtual void print() const = 0;
};

// Task class SelfTravel
// For self organised transport outwards or return define a class with name SelfTravel inheriting public from class Transport with following
// members
class SelfTravel : public Transport
{
    // a public standard constructor
public:
    SelfTravel()
    {
    }

    // a public virtual destructor writing an output message like in the examples below.
    virtual ~SelfTravel()
    {
        cout << "destructor SelfTravel done" << endl;
    }

    // a public virtual member function with name get_price without parameter always returning 0.00 EUR.
    virtual double get_price() const
    {
        return 0.00;
    }

    // a public virtual method with name print without parameter and without return writing "self travel" onto the standard character output
    // stream (see example below).
    virtual void print() const
    {
        cout << "self travel";
    }
};

// Task class PublicTransport
// Define an abstract class with name PublicTransport inheriting public from class Transport with following members:

class PublicTransport : public Transport
{
    // a protected attribute of type Date for the departure.
protected:
    Date departure;

    // a protected C++ string attribute with name code for the flight, train, ...
protected:
    string code;

    // a protected C++ string attribute with name from for the place of departure.
protected:
    string from;

    // a protected C++ string attribute with name to for the place of arrival.
protected:
    string to;

    // a protected real-valued attribute with name priceOneSeat for the price of one seat.
protected:
    double priceOneSeat;

    // a protected Boolean attribute with name firstClass whether the seat is in first class.
protected:
    bool firstClass;

    //   a public constructor with a date as parameter for the departure day, three C++ string parameters to initialise the code, the places of departure
    // and arrival, a parameter for the price of one seat as well as a Boolean default parameter with value false whether first class is wanted

public:
    PublicTransport(Date d, string c, string f, string t, double p, bool fc = false)
    {
        departure = d;
        code = c;
        from = f;
        to = t;
        priceOneSeat = p;
        firstClass = fc;
    }

    // a public virtual destructor writing an output message including the code, date of departure, place of departure and arrival (see examples below).
    virtual ~PublicTransport()
    {
        cout << "destructor PublicTransport " << code << " at " << departure << " from " << from << " to " << to << " done" << endl;
    }


    // a public virtual method with name print without parameter or return writing the date, the code, the places of departure and of arrival, "(first
    // class)" in case of wanted, the price and "EUR/person" in round brackets (see example below)
    virtual void print() const
    {
        cout << departure << " " << code << " from " << from << " to " << to;
        if (firstClass)
        {
            cout << " first class";
            cout << " (" << priceOneSeat * 2 << ".00 EUR/person)";
        }
        else
        {
            cout << " (" << priceOneSeat << ".00 EUR/person)";
        }
    }
};

// Define a class with name Flight inheriting public from class PublicTransport with following members:
class Flight : public PublicTransport
{
    // a protected Boolean attribute with name transfer whether also a transfer between airport and accomodation is included
protected:
    bool transfer;

    // a public constructor with a date as parameter for the departure day, three C++ string parameters to initialise the code of the flight, the
    // airports of departure and arrival, a parameter for the price of one seat, a Boolean default parameter with value false whether the seat shall be
    // first class as well as a further Boolean default parameter with value true whether also a transfer is included.
public:
    Flight(Date d, string c, string f, string t, double p, bool fc = false, bool tr = true)
        : PublicTransport(d, c, f, t, p, fc)
    {
        transfer = tr;
    }

    // a public virtual destructor writing an output message like in the example below.
    virtual ~Flight()
    {
        cout << "destructor Flight done" << endl;
    }

    // a public virtual method with name includedTransfer without parameter returning the value of the respective attribute.
    virtual bool includedTransfer() const
    {
        return transfer;
    }

    // a public virtual method with name get_price without parameter returning the value of attribute priceOneSeat for one seat and its doubled
    // value for a first class seat.
    virtual double get_price() const
    {
        if (firstClass)
        {
            return priceOneSeat * 2;
        }
        else
        {
            return priceOneSeat;
        }
    }


    // a public virtual method with name print without parameter and without return writing "flight " and afterwards calling the same name
    // method of the direct super class (see example below).
    virtual void print() const
    {
        cout << "flight ";
        PublicTransport::print();
    }
};

// Task class Train
// Define a class with name Train inheriting public from class PublicTransport with following members:
class Train : public PublicTransport
{
    // a public constructor with a date as parameter for the departure day, three C++ string parameters to initialise the code of the train, the train
    // stations of departure and arrival, a parameter for the price of one seat and a Boolean default parameter with value false whether the seat shall
    // be first class

    bool transfer;

public:
    Train(Date d, string c, string f, string t, double p, bool fc = false)
        : PublicTransport(d, c, f, t, p, fc)
    {
        transfer = true;
    }

    // a public virtual destructor writing an output message like in the example below.
    virtual ~Train()
    {
        cout << "destructor Train done" << endl;
    }

    virtual bool includedTransfer() const
    {
        return transfer;
    }

    // a public virtual method with name get_price without parameter returning the value of attribute priceOneSeat for a seat in second class and
    // its 1.5 fold value for a first class seat
    virtual double get_price() const
    {
        if (firstClass)
        {
            return priceOneSeat * 1.5;
        }
        else
        {
            return priceOneSeat;
        }
    }

    // a public virtual method with name print without parameter or return value writing "train " and afterwards calling the same name method of
    // the direct super class (see example below).
    virtual void print() const
    {
        cout << "train ";
        PublicTransport::print();
    }
};


// ###############################################

// Define a C++ enumeration (enum struct) with values for no_meals, breakfast, half_board and all_inclusive.
enum Meal
{
    no_meals,
    breakfast,
    half_board,
    all_inclusive
};

// Define an overloaded binary output operator that writes breakfast, half board, all inclusive or otherwise no meals onto the character
// output data stream passed as a parameter depending on the enumeration value.

ostream& operator<<(ostream& output, Meal M)
{
    switch (M)
    {
    case no_meals:
        return output << "no meals";
        break;
    case breakfast:
        return output << "breakfast";
        break;
    case half_board:
        return output << "half board";
        break;
    case all_inclusive:
        return output << "all inclusive";
        break;
    }
}
// Define a function get_price with an object of this enumeration as parameter and a floating point number as return.
// In the body, the price for a breakfast, which costs the same in all accommodations, in the amount of 10 EUR shall be returned, for half board 20
// EUR, for all-inclusive 50 EUR (each per person) and otherwise 0 EUR.

float get_price_board(Meal M)
{
    switch (M)
    {
    case no_meals:
        return 0;
        break;
    case breakfast:
        return 10;
        break;
    case half_board:
        return 20;
        break;
    case all_inclusive:
        return 50;
        break;
    }
}


// Define a class with name Accomodation with following members:
class Accomodation
{

private:
    // a private attribute of type C++ string for the location of the accomodation.
    string location;

    // a private attribute of type Date for the arrival at the accomodation.
    Date arrival;

    // three private integer attributes nights for the number of to book nights, singles for the number of to book single rooms and doubles for
    // the number of to book double rooms.
    int nights;
    int singles;
    int doubles;

    // three private real-valued attributes priceNightSingle for the price of a single room for one night,  priceNightDouble for the price of a
    // double room one night and priceOneDayParking for the price of a parking place one day.
    float priceNightSingle;
    float priceNightDouble;
    float priceOneDayParking;

    // a private attribute of type Board for the desired board
    Meal board;

    // a private Boolean attribute with name parking for an additionally to book parking place.
    bool parking;

public:
    // a public constructor with three parameters for the price of a single room per night, a double room per night and a parking place per night/day.
    // In the body, only the member function ask_data shall be called, via which all other data can be entered and saved..
    Accomodation(float priceNightSingle, float priceNightDouble, float priceOneDayParking)
    {
        this->priceNightSingle = priceNightSingle;
        this->priceNightDouble = priceNightDouble;
        this->priceOneDayParking = priceOneDayParking;
        ask_data();
    }


    // a public destructor outputting a message like shown in the examples below.
    ~Accomodation()
    {
        // destructor Accomodation Berlin at 2023-01-27 for 5 guests done
        // destructor Request 3 done
        cout << "destructor Accomodation " << location << " at " << arrival << " for " << get_guests() << " guests done" << endl;
    }

    // a public member function with name get_arrival without parameter returning the arrival date.
    Date get_arrival()
    {
        return arrival;
    }

    // a public member function with name get_checkout without parameter returning the departure date (arrival date plus number of nights added
    // by above defined operator in class Date).
    Date get_checkout()
    {
        return arrival + nights;
    }

    // xxxxa public member function with name get_guests without parameter returning the number of sleeping guests, e.g. 1 for a booked single
    // room, 4 for two double rooms or 9 for three single and three double rooms booked.
    int get_guests()
    {
        return singles + doubles * 2;
    }

    // a public member function with name get_price without parameters that returns the total number of overnight guests. In the body, add one
    // person for to book single rooms and two persons for to book double rooms, for example 4 for two double rooms or 8 for two single and three
    // double rooms
    float get_price()
    {
        float boardPrice = get_guests();
        // if (board == breakfast)
        // {
        //     boardPrice *= 10;
        // }
        // else if (board == half_board)
        // {
        //     boardPrice *= 20;
        // }
        // else if (board == all_inclusive)
        // {
        //     boardPrice *= 50;
        // }
        boardPrice = get_guests() * get_price_board(board) * nights;
        return (singles * priceNightSingle + doubles * priceNightDouble) * nights + boardPrice + (parking ? priceOneDayParking * nights : 0);

    }
    // a public member function with name ask_data without parameters and without return.
    // In the body, as in the examples below, the location for the accommodation should be requested and initialised, the arrival date and the number
    // of nights (a maximum of 28 nights/4 weeks should be possible to book), how many single and double rooms, what board and whether a parking
    // place should be reserved.
    // Finally, output the calculated price (via a call to get_price()).
    void ask_data()
    {
        cout << "location of accomodation: ";
        cin >> location;
        cout << "arrival on (yyyy-mm-dd): ";
        cin >> arrival;
        cout << "how many nights (max 4 weeks): ";
        cin >> nights;
        cout << "how many single bed rooms (" << priceNightSingle << ".00 EUR/night): ";
        cin >> singles;
        cout << "how many double bed rooms (" << priceNightDouble << ".00 EUR/night): ";
        cin >> doubles;
        cout << "a all inclusive (50.00 EUR/day)" << endl;
        cout << "b breakfast     (10.00 EUR/day)" << endl;
        cout << "h half board    (20.00 EUR/day)" << endl;
        cout << "n no meals" << endl;
        cout << "your choice: ";
        char choice;
        cin >> choice;
        switch (choice)
        {
        case 'a':
            board = all_inclusive;
            break;
        case 'b':
            board = breakfast;
            break;
        case 'h':
            board = half_board;
            break;
        case 'n':
            board = no_meals;
            break;
        }
        // with parking place (10.00 EUR/day; y(es) or n(o)): y
        cout << "with parking place (" << priceOneDayParking << ".00 EUR/day; y(es) or n(o)): ";
        char parking;
        cin >> parking;
        if (parking == 'y') { this->parking = true; }
        else { this->parking = false; }
        cout << "price: " << get_price() << ".00 EUR" << endl;


    }



    // a public member function with name print without parameters and without return.
    // In the body, as in the example below, write the location of the accommodation to be reserved onto the standard character output stream, the
    // number of guests and nights, the arrival and departure dates, the number of single and double rooms to book each with the price for one night
    // in brackets behind it, the meals to book with the price for one person and one day in brackets behind it, as well as for a parking place to be
    // reserved and finally the calculated price.

    void print()
    {
        cout << "accomodation at:      " << location << endl;
        cout << "number of guests:     " << get_guests() << endl;
        cout << "number of nights:     " << nights << endl;
        cout << "check-in date:        " << arrival << endl;
        cout << "check-out date:       " << get_checkout() << endl;
        cout << "single bed room(s):   " << singles << " (" << priceNightSingle << ".00 EUR/night)" << endl;
        cout << "double bed room(s):   " << doubles << " (" << priceNightDouble << ".00 EUR/night)" << endl;
        cout << "board:                " << board << " (" << get_price_board(board) << ".00 EUR/day and person)" << endl;
        cout << "parking:              " << (parking ? "included" : "not included") << " (" << priceOneDayParking << " EUR/day)" << endl;
        cout << "price accomodation:   " << get_price() << ".00 EUR" << endl;
    }

};

// Define a class for a desired reservation Request for an accomodation with following members:

class Request
{

private:
    // a private constant unsigned integer attribute no for a call center uniquely and consecutively assigned request number for each reservation
    // request.
    unsigned int no;

    // a private static unsigned integer class variable with name lastNo to store a sequential number for each reservation request, which is
    // incremented each time a new object of this class is created, which initialises the respective attribute no and thus implements the unique,
    // identifying number of all objects.
    // This static class variable is to be initialised with value 0 - outside the class.
    static unsigned int lastNo;

    // a private pointer attribute accomodation for this reservation request.
    Accomodation* accomodation;

    // a private pointer attribute next to generate a list of reservation requests.
    Request* next;

    // add a private pointer attribute transportOutward for the transport outward of this reservation request.
    Transport* transportOutward;

    // add a private pointer attribute transportReturn for the transport return of this reservation request.
    Transport* transportReturn;

public:
    // a public constructor with a pointer to an accommodation of type Accomodation and a default pointer parameter of type Request with default
    // value null pointer.
    // Initialise the number no of this request with the value of the incremented class attribute lastNo and the other two attributes with the respective
    // parameters
    Request(Accomodation* accomodation, Request* next = nullptr, Transport* transportOutward = nullptr, Transport* transportReturn = nullptr)
    {
        this->accomodation = accomodation;
        this->next = next;
        no = ++lastNo;
        this->transportOutward = transportOutward;
        this->transportReturn = transportReturn;
    }

    // a public destructor that also deletes the reservation request and makes a corresponding output as in the example below.
    ~Request()
    {
        cout << "Request " << no << " deleted" << endl;
        delete accomodation;
        cout << "Transport outward deleted" << endl;
        cout << "Transport return deleted" << endl;
        delete transportOutward;
        delete transportReturn;

    }

    // a public member function with name get_no without parameter returning the number of the trip.
    unsigned int get_no()
    {
        return no;
    }

    // a public member function with name get_next without parameter returning a pointer to the next reservation request within the list.
    Request* get_next()
    {
        return next;
    }

    // a public member function with name set_next and a pointer to a reservation request as parameter assigning it as next request within the list.
    void set_next(Request* next)
    {
        this->next = next;
    }

    // a public member function with name get_price without parameter returning the calculated price of the accomodation.
    float get_price()
    {
        // return accomodation->get_price();
        float price = accomodation->get_price();
        // if (transportOutward != nullptr)
        // {
        //     price += transportOutward->get_price();
        // }
        // if (transportReturn != nullptr)
        // {
        //     price += transportReturn->get_price();
        // }
        return price;
    }

    // a public member function with name print without parameter or return value that writes the number of the request and the desired
    // accommodation to the standard character output stream (see example below).
    void print()
    {
        // ********REQUEST NO: 1********
        cout << "********REQUEST NO: " << no << "********" << endl;
        accomodation->print();

        if (transportOutward != nullptr)
        {
            cout << "outward journey:      ";
            transportOutward->print();
            if (transportOutward->includedTransfer())
            {
                cout << " transfer included";
            }
            else
            {
                cout << " no transfer";
            }
            cout << endl;
        }
        if (transportReturn != nullptr)
        {
            cout << "journey back:         ";
            transportReturn->print();
            if (transportReturn->includedTransfer())
            {
                cout << " transfer included";
            }
            else
            {
                cout << " no transfer";
            }
            cout << endl;
        }

        cout << "price total:        " << get_price() + (transportOutward->get_price() * accomodation->get_guests()) + (transportReturn->get_price() * accomodation->get_guests()) << ".00 EUR" << endl;


    }
};
// Initialise the static class variable lastNo with value 0.
unsigned int Request::lastNo = 0;

// Define a class with name CallCenter with following members:

class CallCenter
{

private:
    // a private pointer attribute requests as head of a list of accomodation requests in this call center.
    Request* requests;

public:

    // a public standard constructor initialising the head of the list with a null pointer.
    CallCenter()
    {
        requests = nullptr;
    }

    // a public method with name append with a pointer to a reservation request as parameter without return inserting it at the end of the list of
    // requests
    void append(Request* request)
    {
        if (requests == nullptr)
        {
            requests = request;
        }
        else
        {
            Request* current = requests;
            while (current->get_next() != nullptr)
            {
                current = current->get_next();
            }
            current->set_next(request);
        }
    }

    // a public method with name cancel with a pointer to a reservation request as parameter without return deleting this request from the list.
    void cancel(Request* request)
    {
        if (requests == request)
        {
            requests = request->get_next();
            delete request;
        }
        else
        {
            Request* current = requests;
            while (current->get_next() != request)
            {
                current = current->get_next();
            }
            current->set_next(request->get_next());
            delete request;
        }
    }

    // a public method with name get_request with a number as parameter searching for the reservation request with this number and returning a
    // pointer to it or otherwise a null pointer.

    Request* get_request(unsigned int no)
    {
        Request* current = requests;
        while (current != nullptr)
        {
            if (current->get_no() == no)
            {
                return current;
            }
            current = current->get_next();
        }
        return nullptr;
    }

    // a public method with name print_all without parameter or return outputting all reservation requests within the list (see example below).
    void print_all()
    {
        Request* current = requests;
        while (current != nullptr)
        {
            current->print();
            current = current->get_next();
        }
    }

};



// function to get transport from user
Transport* get_transport(Date  d)
{
    cout << "0 self travel" << endl;
    cout << "1 by flight" << endl;
    cout << "2 by train" << endl;
    cout << "your choice: ";
    int choice_return;
    cin >> choice_return;
    cin.ignore();
    // pointer to store any transport
    Transport* transport_return = nullptr;

    switch (choice_return)
    {
    case 0:
    {
        // self travel
        transport_return = new SelfTravel();
        break;
    }
    case 1:
    {
        // by flight
        string code;
        string airport_of_departure;
        string airport_of_arrival;
        double standard_price;
        bool first_class;

        cout << "code of flight: ";
        getline(cin, code);
        cout << "airport of departure: ";
        getline(cin, airport_of_departure);
        cout << "airport of arrival: ";
        getline(cin, airport_of_arrival);
        cout << "standard price for one passenger: ";
        cin >> standard_price;
        cin.ignore();
        cout << "first class ((y)es or (n)o): ";
        char first_class_char;
        cin >> first_class_char;
        cin.ignore();
        if (first_class_char == 'y')
        {
            first_class = true;
        }
        else
        {
            first_class = false;
        }
        //                Flight(Date d, string c, string f, string t, double p, bool fc=false, bool tr=true)
        transport_return = new Flight(d, code, airport_of_departure, airport_of_arrival, standard_price, first_class);
        break;
    }

    case 2:
    {
        // by train
        string code;
        string main_train_station_of_departure;
        string main_train_station_of_arrival;
        double price;
        bool first_class;

        cout << "code of train: ";
        getline(cin, code);
        cout << "main train station of departure: ";
        getline(cin, main_train_station_of_departure);
        cout << "main train station of arrival: ";
        getline(cin, main_train_station_of_arrival);
        cout << "first class ((y)es or (n)o): ";
        char first_class_char;
        cin >> first_class_char;
        cin.ignore();
        cout << "price for one passenger: ";
        cin >> price;
        cin.ignore();
        if (first_class_char == 'y')
        {
            first_class = true;
        }
        else
        {
            first_class = false;
        }
        // Train(Date d, string c, string f, string t, double p, bool fc=false, bool tr=true)
        transport_return = new Train(d, code, main_train_station_of_departure, main_train_station_of_arrival, price, first_class);
        break;
    }

    default:
        break;
    }
    return transport_return;
}


int main()
{
    CallCenter callCenter;

    // hanlde requests pointer and allocate memory
    Request* request = nullptr;
    Request* tail = nullptr;

    int choice = 0;
    do
    {
        cout << "\n\nCALL CENTER BOOKING REQUEST" << endl;
        cout << "0 end" << endl;
        cout << "1 new reservation request standard" << endl;
        cout << "2 new reservation request superior" << endl;
        cout << "3 show reservation request" << endl;
        cout << "4 show all reservation requests" << endl;
        cout << "your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 0:
            break;
        case 1:
        {
            Accomodation* accomodation = new Accomodation(80.00, 150.00, 10.00);
            cout << "please choose transport outward" << endl;
            Transport* transport_outward = get_transport(accomodation->get_arrival());

            cout << "please choose transport return" << endl;
            Transport* transport_return = get_transport(accomodation->get_checkout());

            if (request != nullptr)
            {
                tail->set_next(new Request(accomodation, nullptr, transport_outward, transport_return));
                tail = tail->get_next();
            }
            else
            {

                Request* request_standard = new Request(accomodation, request, transport_outward, transport_return);
                request = request_standard;
                tail = request_standard;
            }

            break;


        }
        case 2:
        {
            Accomodation* accomodation = new Accomodation(110.00, 210.00, 10.00);

            cout << "please choose transport outward" << endl;
            Transport* transport_outward = get_transport(accomodation->get_arrival());

            cout << "please choose transport return" << endl;
            Transport* transport_return = get_transport(accomodation->get_checkout());


            if (request != nullptr)
            {
                tail->set_next(new Request(accomodation, nullptr, transport_outward, transport_return));
                tail = tail->get_next();

            }
            else
            {

                Request* request_superior = new Request(accomodation, request, transport_outward, transport_return);
                request = request_superior;
                tail = request_superior;
            }
            break;
        }
        case 3:
        {
            cout << "Request number: ";
            int request_number;
            cin >> request_number;

            Request* current = request;
            while (current != nullptr)
            {
                if (current->get_no() == request_number)
                {
                    current->print();
                    break;
                }
                current = current->get_next();
            }
            if (current == nullptr)
            {
                cout << "Invalid request number!" << endl;
            }
            else
            {
                // (c)ancel this request or (n)ot: c
                // destructor Accomodation Berlin at 2023-01-27 for 5 guests done
                // destructor Request 3 done

                cout << "(c)ancel this request or (n)ot: ";
                char cancel;
                cin >> cancel;
                if (cancel == 'c')
                {
                    Request* current = request;
                    Request* previous = nullptr;
                    int counter = 1;
                    while (current != nullptr)
                    {
                        if (current->get_no() == request_number)
                        {
                            if (previous != nullptr)
                            {
                                previous->set_next(current->get_next());
                            }
                            else
                            {
                                request = current->get_next();
                            }
                            delete current;
                            cout << "destructor Request " << request_number << " done" << endl;
                            break;
                        }
                        previous = current;
                        current = current->get_next();
                        counter++;
                    }
                }

                // set tail pointer to last request
                current = request;
                while (current != nullptr)
                {
                    tail = current;
                    current = current->get_next();
                }
            }

            break;
        }
        case 4:
        {
            Request* current = request;
            while (current != nullptr)
            {
                current->print();
                current = current->get_next();
            }
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 0);
}


