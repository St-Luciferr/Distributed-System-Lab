package Lab2.Factorial;

import java.math.BigInteger;

// Creating an Interface
public interface Factorial extends java.rmi.Remote {

	// Declaring the method
	public BigInteger fact(int num)
		throws java.rmi.RemoteException;
}
