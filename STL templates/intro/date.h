const int days_in_month[] /* File: date.h */
     = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date     // Only for non-leap years
{
  private:
    int days;  // Days in a non-leap year; must be within [1, 365]
  public:
    Date(int n): days((n < 1 || n > 365) ? 1 : n) { }
    bool operator>(const Date& x) const { return (days > x.days); }

    int month() const
    {
        for (int remain_days = days, m = 0; m < 12; ++m)
            if (remain_days <= days_in_month[m]) return m+1;
            else remain_days -= days_in_month[m];
    }

    int day() const
    {
        for (int remain_days = days, m = 0; m < 12; ++m)
            if (remain_days <= days_in_month[m]) return remain_days;
            else remain_days -= days_in_month[m];
    }
};
