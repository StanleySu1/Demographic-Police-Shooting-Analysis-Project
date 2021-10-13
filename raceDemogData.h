#ifndef RACEDEMOG_H
#define RACEDEMOG_H

#include <iostream>

class raceDemogData {
  public:
  		//default constructor
  	    raceDemogData() :
            NativeCount(0), AsianCount(0), BlackCount(0), LatinoCount(0), HIPacificIsleCount(0),
            MultiRaceCount(0), WhiteCount(0), WhiteNHCount(0), otherCount(0), communityCount(0) {}

        //For state demographic 
        raceDemogData(int N, int A, int B, int L, int HPI, int MR, int W, int WNH,  int size) :
            NativeCount(N), AsianCount(A), BlackCount(B), LatinoCount(L), HIPacificIsleCount(HPI),
            MultiRaceCount(MR), WhiteCount(W), WhiteNHCount(WNH), otherCount(0), communityCount(size) {}

        //For state police shootings (if ncessary)
        raceDemogData(int N, int A, int B, int L, int W, int WNH, int O, int size) :
            NativeCount(N), AsianCount(A), BlackCount(B), LatinoCount(L), HIPacificIsleCount(0),
            MultiRaceCount(0), WhiteCount(W), WhiteNHCount(WNH), otherCount(O), communityCount(size) {}

      double getNativePercent() const  { return 100.0f*(double)(NativeCount)/communityCount; }
   		double getAsianPercent() const { return 100.0f*(double)(AsianCount)/communityCount; }
    	double getBlackPercent() const { return 100.0f*(double)(BlackCount)/communityCount; }
    	double getLatinoPercent() const { return 100.0f*(double)(LatinoCount)/communityCount; }
    	double getHIPacificIslePercent() const  { return 100.0f*(double)(HIPacificIsleCount)/communityCount; }
    	double getMultiRacePercent() const { return 100.0f*(double)(MultiRaceCount)/communityCount; }
    	double getWhitePercent() const { return 100.0f*(double)(WhiteCount)/communityCount; }
      double getWhiteNHPercent() const { return 100.0f*(double)(WhiteNHCount)/communityCount; }
      double getOtherPercent() const { return 100.0f*(double)(otherCount)/communityCount; }

      int getNativeCount() const { return NativeCount; }
      int getAsianCount() const { return AsianCount; }
      int getBlackCount() const { return BlackCount; }
      int getLatinoCount() const { return LatinoCount; }
      int getHIPacificIsleCount() const { return HIPacificIsleCount; }
      int getMultiRaceCount() const  { return MultiRaceCount; }
      int getWhiteCount() const { return WhiteCount; }
      int getWhiteNHCount() const { return WhiteNHCount; }
      int getOtherCount() const { return otherCount; }
      int getCommunityCount() const { return communityCount; }

      void addNativeCount(int inNum)  { NativeCount += inNum; communityCount += inNum;   }
      void addNativeNoComCount(int inNum)  { NativeCount += inNum;}
      void addAsianCount(int inNum)    { AsianCount+= inNum; communityCount += inNum; }
      void addAsianNoComCount(int inNum)    { AsianCount+= inNum;}
      void addBlackCount(int inNum)    { BlackCount+= inNum; communityCount += inNum;}
      void addBlackNoComCount(int inNum)    { BlackCount+= inNum;}
      void addLatinoCount(int inNum)   { LatinoCount+= inNum; communityCount += inNum;}
      void addLatinoNoComCount(int inNum) {LatinoCount+= inNum;}
      void addHIPacificIsleCount(int inNum)    { HIPacificIsleCount+= inNum; communityCount += inNum;}
      void addHIPacificIsleNoComCount(int inNum)    { HIPacificIsleCount+= inNum;}
      void addMultiRaceCount(int inNum)     { MultiRaceCount+= inNum; communityCount += inNum;}
      void addMultiRaceNoComCount(int inNum)     { MultiRaceCount+= inNum;}
      void addWhiteCount(int inNum)    { WhiteCount+= inNum; communityCount += inNum;}
      void addWhiteNoComCount(int inNum)    { WhiteCount+= inNum;}
      void addWhiteNHCount(int inNum)    { WhiteNHCount+= inNum; communityCount += inNum;}
      void addWhiteNHNoComCount(int inNum) {WhiteNHCount += inNum;}
      void addOtherCount(int inNum)    { otherCount+= inNum; communityCount += inNum;}
      void addOtherNoComCount(int inNum)    { otherCount+= inNum;}
      void addCommunityCount(int inNum)   { communityCount+= inNum; }

      raceDemogData& operator+=(const raceDemogData rd) {
        NativeCount += rd.NativeCount;
        AsianCount += rd.AsianCount;
        BlackCount += rd.BlackCount;
        LatinoCount += rd.LatinoCount;
        HIPacificIsleCount += rd.HIPacificIsleCount;
        MultiRaceCount += rd.MultiRaceCount;
        WhiteCount += rd.WhiteCount;
        WhiteNHCount += rd.WhiteNHCount;
        otherCount += rd.otherCount;
        communityCount += rd.communityCount;

        return *(this);
    }

    friend std::ostream& operator<<(std::ostream &out, const raceDemogData &SD);

  private:
  	//count of population for various racial/ethinic identifies 
  	//from US census (assumes 'alone' except LatinX, Multiracial, White)
    int NativeCount; //Native American/First Nation
    int AsianCount; //Asian American
    int BlackCount; //African American/Black
    int LatinoCount; //Hispanic/Latinx
    int HIPacificIsleCount; //Hawaiian Pacific Islander
    int MultiRaceCount; //Multi-racial
    int WhiteCount; //White (includes Hispanic)
    int WhiteNHCount; //White non-Hispanic
    int otherCount; //Other category used for other data sources
    int communityCount;
};

#endif