package com.sanris.msc.hashp;

import java.math.BigInteger;

public interface Hash {

   static long coreMemory = 0;

  public boolean free();
  public boolean duplicate();
  public boolean del();
  public boolean optimize();
  public boolean defragement();
  public boolean rebalance();
  public boolean serialize();
  public boolean config();
  public long getCoreMemory();
  public BigInteger getData(String size);
}
