#if !defined date
# define date
class  Date
{

public:
	Date();
	Date(int y);
	Date(int date_y, int date_m, int date_d);
	void setDate(int d_y, int d_m, int d_d);
	void showDate() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;

private:
	int year;
	int month;
	int day;
};

#endif
