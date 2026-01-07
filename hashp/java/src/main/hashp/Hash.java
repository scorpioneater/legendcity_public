package com.sanris.msc.hashp;

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
}
