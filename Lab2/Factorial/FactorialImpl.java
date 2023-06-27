package Lab2.Factorial;

import java.math.BigInteger;

// Extends and Implement the class and interface respectively
public class FactorialImpl
	extends java.rmi.server.UnicastRemoteObject
	implements Factorial {

	// Constructor Declaration
	public FactorialImpl()
		throws java.rmi.RemoteException
	{
		super();
	}


	// Implementation of the method fact()
	public BigInteger fact(int num)
		throws java.rmi.RemoteException
	{
		BigInteger factorial = BigInteger.ONE;

		for (int i = 1; i <= num; ++i) {
			factorial = factorial
							.multiply(
								BigInteger
									.valueOf(i));
		}
		return factorial;
	}
}
