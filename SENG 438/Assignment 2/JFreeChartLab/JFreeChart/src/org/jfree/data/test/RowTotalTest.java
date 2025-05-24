package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.DataUtilities;
import org.jfree.data.Values2D;
import org.jmock.Expectations;
import org.jmock.Mockery;
import org.junit.Before;
import org.junit.Test;

/*
calculateRowTotal(Values2D data, int row)
Purpose: Calculates the sum of all values in a specified row of a data table.
Parameters:

data: A Values2D object containing the data table (must not be null)
row: The row index (zero-based) to sum

Return Value: The sum of all values in the specified row as a double

*/



//mock Values2D interface to create a mock object for testing.


public class RowTotalTest extends DataUtilities {
    private Mockery mockingContext;

    @Before
    public void setUp() {
        mockingContext = new Mockery();
    }

    @Test
    public void calculateRowTotal_AllPositiveValues_ReturnsSum() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getColumnCount();
                will(returnValue(3));
                one(values).getValue(0, 0);
                will(returnValue(1.0));
                one(values).getValue(0, 1);
                will(returnValue(2.0));
                one(values).getValue(0, 2);
                will(returnValue(0.0));  
            }
        });

 
        double result = DataUtilities.calculateRowTotal(values, 0);

        
       
        assertEquals("Sum of row with positive values should be 3.0", 3.0, result, .000000001d);
    }

    
    @Test
    public void calculateRowTotal_MixedValues_ReturnsSum() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getColumnCount();
                will(returnValue(3));
                one(values).getValue(1, 0);
                will(returnValue(-2.0));
                one(values).getValue(1, 1);
                will(returnValue(2.0));
                one(values).getValue(1, 2);
                will(returnValue(0.0));
            }
        });

    
        double result = DataUtilities.calculateRowTotal(values, 1);


        assertEquals("Sum of row with mixed values should be 0.0", 0.0, result, .000000001d);
    }
    
    

    @Test
    public void calculateRowTotal_EmptyDataTable_ReturnsZero() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getColumnCount();
                will(returnValue(0));
            }
        });


        double result = DataUtilities.calculateRowTotal(values, 0);


        assertEquals("Sum of empty row should be 0.0", 0.0, result, .000000001d);
    }

    @Test(expected = NullPointerException.class)
    public void calculateRowTotal_NullData_ThrowsNullPointerException() {

        DataUtilities.calculateRowTotal(null, 0);
    }
    
    @Test
    public void calculateRowTotal_NullValuesInData_SkipsNullValue() {

        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getColumnCount();
                will(returnValue(3));
                one(values).getValue(0, 0);
                will(returnValue(1.0));
                one(values).getValue(0, 1);
                will(returnValue(2.0));
                one(values).getValue(0, 2);
                will(returnValue(null));  
            }
        });


        double result = DataUtilities.calculateRowTotal(values, 0);

  
        assertEquals("Sum of row with null value should be 3.0", 3.0, result, .000000001d);
    }
}