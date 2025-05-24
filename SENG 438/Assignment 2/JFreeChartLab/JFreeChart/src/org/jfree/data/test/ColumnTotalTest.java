
package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.DataUtilities;
import org.jfree.data.Values2D;
import org.jmock.Expectations;
import org.jmock.Mockery;
import org.junit.Before;
import org.junit.Test;
import java.lang.NullPointerException;

/*
calculateColumnTotal(Values2D data, int column)
Purpose: Calculates the sum of all values in a specified column of a data table.
Parameters:
data: A Values2D object containing the data table (must not be null)
column: The column index (zero-based) to sum

Return Value: The sum of all values in the specified column as a double
*/




// mock Values2D interface to create a mock object for testing.

public class ColumnTotalTest extends DataUtilities {
    private Mockery mockingContext;

    @Before
    public void setUp() {
        mockingContext = new Mockery();
    }

 // 
    
    @Test
    public void calculateColumnTotal_AllPositiveValues_ReturnsSum() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getRowCount();
                will(returnValue(3));
                one(values).getValue(0, 0);
                will(returnValue(7.5));
                one(values).getValue(1, 0);
                will(returnValue(2.5));
                one(values).getValue(2, 0);
                will(returnValue(5.0));
            }
        });


        double result = DataUtilities.calculateColumnTotal(values, 0);


        assertEquals("Sum of column with positive values should be 15.0", 15.0, result, .000000001d);
    }

    @Test
    public void calculateColumnTotal_MixedValues_ReturnsSum() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getRowCount();
                will(returnValue(3));
                one(values).getValue(0, 1);
                will(returnValue(-5.0));
                one(values).getValue(1, 1);
                will(returnValue(2.0));
                one(values).getValue(2, 1);
                will(returnValue(3.0));
            }
        });


        double result = DataUtilities.calculateColumnTotal(values, 1);


        assertEquals("Sum of column with mixed values should be 0.0", 0.0, result, .000000001d);
    }

    @Test
    public void calculateColumnTotal_EmptyDataTable_ReturnsZero() {
        // setup
        final Values2D values = mockingContext.mock(Values2D.class);
        mockingContext.checking(new Expectations() {
            {
                one(values).getRowCount();
                will(returnValue(0));
            }
        });


        double result = DataUtilities.calculateColumnTotal(values, 0);


        assertEquals("Sum of empty column should be 0.0", 0.0, result, .000000001d);
    }

    @Test(expected = NullPointerException.class)  
    public void calculateRowTotal_NullData_ThrowsIllegalArgumentException() {  

        DataUtilities.calculateRowTotal(null, 0);
    }
    
}

