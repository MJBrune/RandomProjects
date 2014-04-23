#include "Date.h"

namespace MB_DATETIME
{
	//-----------------------------------------------------------------------------
	//		method:			Date(short day, short month, short year) -- constructor
	//
	//		description:	creates a new Date object
	// 
	//    Calls:            setCurrentDate()
	//						daysInMonth(month, year)
	//						setDayOfYear()
	//						setDayOfWeek()
	// 
	//    Called By:		ostream& operator<<(ostream& sout, const CComplex &c)
	// 
	//    Parameters:		short day		-- day to set
	//						short month		-- month to set
	//						short year		-- month to set
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	Date::Date(short day, short month, short year)
	{
		setCurrentDate();
		if ( year >= LOWYEAR && month <= MAXMONTH && month >= MINMONTH && day >= 0 && day <= daysInMonth(month, year) )
		{
			m_year = year;
			m_month = month;
			m_dayOfMonth = day;
		}

		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			operator==(const Comparable& other)const
	//
	//		description:	true if the two objects are exactly the same
	// 
	//    Parameters:		const Comparable &other  -- the other Date to compare
	//
	//	  Exceptions:		throws bad_cast if other is not a Date
	// 
	//    Returns:          true if the two objects are exactly the same
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	bool Date::operator==(const Comparable &other)const
	{
		try
		{
			const Date &otherDate = dynamic_cast<const Date&>(other);
			if(m_year == otherDate.m_year && m_dayOfYear ==
				otherDate.m_dayOfYear)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
	}
	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			lessThan(const Comparable& other)const
	//
	//		description:	true if the current object is before other
	// 
	//    Parameters:		const Comparable &other  -- the other Date to compare
	// 
	//    Returns:          true if the current object is before other
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	bool Date::operator<(const Comparable &other)const
	{
		try
		{
			const Date &otherDate = dynamic_cast<const Date&>(other);
			if(m_year < otherDate.m_year || m_dayOfYear <
				otherDate.m_dayOfYear)
				return true;
			return false;   
		}
		catch(bad_cast e)
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setCurrentDate()
	//
	//		description:	sets the date from the system clock
	// 
	//    Called By:		constructor, mutators
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setCurrentDate(void)
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_year = currentTimePtr->tm_year + 1900;
		m_month = currentTimePtr->tm_mon;
		m_dayOfMonth = currentTimePtr->tm_mday;
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setDayOfWeek(void)
	//
	//		description:	sets the proper day of the week
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setDayOfWeek(void)
	{
		long day = 2;
		for ( int i = LOWYEAR; i <= m_year; i++ )
		{
			if (isLeapYear(i))
				day++;
			day++;
		}
		day += m_dayOfYear;
		m_dayOfWeek = day % DAYSINWEEK;
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setDayOfYear(void)
	//
	//		description:	sets the proper day of the year
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setDayOfYear(void)
	{
		int days = 0;

		for (int i = 0; i < m_month; ++i)
			days += daysInMonth(i, m_year);
		days += m_dayOfMonth;
		m_dayOfYear = days;
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			countLeaps(short year)const
	//
	//		description:	returns the number of leap years from 1760 to year
	// 
	//    Calls:            isLeapYear(short)
	// 
	//    Returns:          the number of leap years from 1760 to year 
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	short Date::countLeaps(short year)const
	{ 
		short leaps = LEAPYEARSTART;
		for(short i = LOWYEAR; i < year; i++)
			if(isLeapYear(i))
				leaps++; 
		return leaps;
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setDayOfMonth(short dayOfMonth)
	//
	//		description:	mutator for m_dayOfMonth
	// 
	//    Calls:            daysInMonth(short, short)
	//						setDayOfYear()
	//						setDayOfWeek()
	// 
	//    Parameters:		dayOfMonth --  day of month to set
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setDayOfMonth(short dayOfMonth)
	{
		if(dayOfMonth > 0 && dayOfMonth <= daysInMonth(m_month, m_year))
		{
			m_dayOfMonth = dayOfMonth;
		}
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setMonth(short dmonth)
	//
	//		description:	mutator for m_month
	// 
	//    Calls:            daysInMonth(short, short)
	//						setDayOfYear()
	//						setDayOfWeek()
	//    Called By:		n/a
	// 
	//    Parameters:		month --  month to set
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setMonth(short month)
	{
		if ( month <= MAXMONTH && month <= MINMONTH)
			m_month = month;
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			setYear(short year)
	//
	//		description:	mutator for m_year
	// 
	//    Calls:            isLeapYear(short)
	//						setDayOfYear()
	//						setDayOfWeek()
	// 
	//    Parameters:		year --  year to set
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setYear(short year)
	{
		if ( year >= LOWYEAR)
			m_year = year;
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			input(istream& sin)
	//
	//		description:	input method for Date class
	// 
	//    Calls:            daysInMonth(m_month, m_year)
	// 
	//    Parameters:		sin --  stream to grab input from
	//
	//	  Returns:			sin -- returned to allow continous streams
	//
	//    History Log:
	//                           4/14/12  MB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::input(istream& sin)
	{
		int day;
		int month;
		int year;

		sin >> month;
		sin.ignore();

		sin >> day;
		sin.ignore();

		sin >> year;
		setCurrentDate();

		*this = Date(day, month-1, year);
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			tomorrow()
	//
	//		description:	gets tomorrows date of the current date.
	// 
	//    Calls:            daysInMonth(m_month, m_year)
	//						setMonth()
	//						setYear()
	//						setDayofYear()
	//						setDayOfWeek()
	//	
	//	  Returns:			Tomorrow's Date
	//
	//    History Log:
	//                           4/14/12  MB  completed version 1.0
	//-----------------------------------------------------------------------------
	Date Date::tomorrow()const
	{
		Date tomorrow = *this;
		if (tomorrow.getDayOfMonth() == daysInMonth(m_month, m_year) )
		{
			if ( tomorrow.getMonth() == 11 )
			{
				tomorrow.setMonth(0);
				tomorrow.setYear(m_year+1);
			}
			else
				tomorrow.setMonth(m_month+1);
			tomorrow.setDayOfMonth(1);
		}
		else
			tomorrow.setDayOfMonth(m_dayOfMonth+1);
		tomorrow.setDayOfYear();
		tomorrow.setDayOfWeek();
		return tomorrow;
	}

	//-----------------------------------------------------------------------------
	//    Class:			Date
	//		method:			yesterday()
	//
	//		description:	gets yesterdays date of the current date.
	// 
	//    Calls:            daysInMonth(m_month, m_year)
	//						setMonth()
	//						setYear()
	//						setDayofYear()
	//						setDayOfWeek()
	//	
	//	  Returns:			yesterday's Date
	//
	//    History Log:
	//                           4/14/12  MB  completed version 1.0
	//-----------------------------------------------------------------------------
	Date Date::yesterday()const
	{
		Date yesterday = *this;
		if (m_dayOfMonth == 1)
		{
			if ( m_month == 0 )
			{
				yesterday.setMonth(11);
				yesterday.setYear(m_year-1);
			}
			else
				yesterday.setMonth(m_month-1);
			yesterday.setDayOfMonth(daysInMonth(yesterday.getMonth(),yesterday.getYear()));
		}
		else
			yesterday.setDayOfMonth(m_dayOfMonth-1);
		return yesterday;
	}

	bool Date::isLeapYear(short year)
	{
		if (year % 4 == 0)
		{
			if (year % 100 == 0)
			{
				if (year % 400 == 0)
					return true;
				return false;
			}
			return true;
		}
		return false;
	}
	ostream& operator<<(ostream& sout, const Date& date)
		{date.print(sout); return sout;}
	istream& operator>>(istream& sin, Date& date)
		{date.input(sin); return sin;}
}