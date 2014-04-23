
int Decode(unsigned int *&data_point)
{

    unsigned int TModV830AC::facqreg[2] = {0x100E, 0x0001};
    unsigned int TModV830AC::fMaxDataVal = 200;

    static const short DataHeaderRsh=         26;        //Left shift of a int data to check if this is the Data Header
    static const short DataHeaderLsh=          5;
    static const int   DataHeaderMask= 0x4000000;
    static const short DataMarkMask=         0x0;
    static const short GeoRsh=                27;
    static const short CNTRsh=                18;
    static const short CNTLsh=                 8;
    static const short TSLsh=                 14;
    static const short TSRsh=                 16;
    static const short ChNumbRsh=             27;
    static const short ChNumbLsh=              0;
    static const short DataValueLsh=           6;
    static const short DataValueRsh=           6;
    static const int   TriggNumMask=      0xFFFF;

    static const short GeoAddrOffset=     0x1110;
    static const short GeoMask=             0x1F;
    static const short MaxGeo=                31;
    static const short AMNESIA_Mask=        0x10;
    static const short StaReg1AddrOffset= 0x100E;
    static const short ConBitSetReg=      0x110A;
    static const short EnableDataHeader=    0x20;
    static const short Enable26bitMode=      0x4;

    static unsigned int ChTempData[TModV830AC::fMaxChannel];

    //CleanChData();
    unsigned int tdata = (*data_point);
    unsigned short ChannelNums = 0;
    unsigned int TrigNums = 0, TrigType = 0;
    unsigned int dataMarker = tdata & DataHeaderMask;
    unsigned int mGeo = (tdata>>GeoRsh);

    if(mGeo != fGeo)
    {
	cout<< GetName() << " Data header error. Module Geo " << fGeo << " in Crate: " << fCrateNum <<"  do not match." << endl;
	data_point++;
	return 0;
    }
    if(dataMarker>0)
    {
	ChannelNums = (tdata<<CNTLsh)>>(CNTLsh+CNTRsh);
	TrigType = (tdata<<TSLsh)>>(TSLsh+TSRsh);
	TrigNums = tdata&TriggNumMask;
    }
    for(unsigned int ch=0; ch<ChannelNums; ch++)
    {
	data_point++;
	tdata = (*data_point);
	unsigned short channel = tdata>>ChNumbRsh;
	dataMarker = tdata & DataHeaderMask;
	if(dataMarker != 0)
	{
	    cout << GetName() << " Data error. Too much headers in Module Geo: " << fGeo 
		 << " in Crate: " << fCrateNum << endl;
	    return 0;
	}
	if(channel>=fMaxChannel)
	{
	    cout << GetName() << " Data header error. Module channel: " << channel 
		 << "> fMaxChannel: " << fMaxChannel << endl;
	    continue;
	}
	try
	{
	    unsigned int temp = (tdata<<DataValueLsh)>>DataValueRsh;
	    unsigned int htemp = 0;
	    chdata[channel] = temp;
	    if(temp < ChTempData[channel])
	      htemp = 0x4000000 + temp - ChTempData[channel];
	    else
	      htemp = temp - ChTempData[channel];
	    if(htemp>fMaxDataVal) htemp = fMaxDataVal;

	    ChTempData[channel] = temp;
	    if(htemp>0)
	    {
		if(his1d[channel]) his1d[channel]->Fill(htemp);
	    }
	}
	catch (exception& e)  //want to catch the Array Index Out Of Bounds Exception
	{
	    cerr << "exception caught: " << e.what() << endl;
	}

    }
    //data_point++; //to next data header
    return TrigNums;
}


