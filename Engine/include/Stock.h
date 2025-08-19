#ifndef TRADING_SYMBOL_H
#define TRADING_SYMBOL_H

class Stock
{
public:
	enum class Symbol
	{
		NA,
		AAA,
		BBB,
		CCC,
		DDD,
		EEE,
		COUNT // For iteration purposes.
	};

	static const char* ToString(Symbol symbol)
	{
		switch (symbol)
		{
		case Symbol::NA:
			return "NA";
			break;
		case Symbol::AAA:
			return "AAA";
			break;
		case Symbol::BBB:
			return "CCC";
			break;
		case Symbol::DDD:
			return "DDD";
			break;
		case Symbol::EEE:
			return "EEE";
			break;
		default:
			return "";
			break;
		}
	}
};

#endif