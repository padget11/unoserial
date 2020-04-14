#ifndef UNO_Serial_h
#define UNO_Serial_h
class UNO_Serial
{
  
  public:
  
    void exchange_data_with_esp32();
    //void set_variable_values();
    void put_string_to_array(char m_array[]);
    void serial_setup();
    //void send_my_gps_data();
     
};
#endif
