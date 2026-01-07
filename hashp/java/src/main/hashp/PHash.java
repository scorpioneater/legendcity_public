package com.sanris.msc.hashp;

//import 

public class PHash implements Hash {

  public boolean free() {
     return true;
  }
  public boolean duplicate(){
     return true;
  }
  public boolean del(){
     return true;
  }
  public boolean optimize(){
     return true;
  }
  public boolean defragement(){
     return true;
  }
  public boolean rebalance(){
     return true;
  }
  public boolean serialize(){
     return true;
  }
  public boolean config(){
     return true;
  }
  public long getCoreMemory(){
     return true;
  }
  public BigInteger getData(String size){
     return new BigInteger("782369323");
  }
}
