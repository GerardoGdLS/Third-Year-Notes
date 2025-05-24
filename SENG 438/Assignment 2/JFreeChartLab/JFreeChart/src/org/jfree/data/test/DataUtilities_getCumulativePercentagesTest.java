package org.jfree.data.test;

import static org.junit.Assert.*; 
import org.jfree.data.DataUtilities;
import org.jfree.data.KeyedValues;
import org.jmock.*;
import org.junit.*;
import java.util.ArrayList;


public class DataUtilities_getCumulativePercentagesTest {

	private KeyedValues values;
	
    @Before
    public void setUp() throws Exception { 
	    Mockery mockingContext = new Mockery();
	    values = mockingContext.mock(KeyedValues.class);
	    
	    ArrayList<Integer> keys = new ArrayList<>();
	    keys.add(0);
	    keys.add(1);
	    keys.add(2);
	    
	    mockingContext.checking(new Expectations() {{
	        // getItemCount
	        allowing(values).getItemCount();
	        will(returnValue(3));
	        
			// getKeys
            allowing(values).getKeys();
			will(returnValue(keys));
			
			// getValue
			allowing(values).getValue(0);
			will(returnValue(5));
			allowing(values).getValue(1);
			will(returnValue(9));
			allowing(values).getValue(2);
			will(returnValue(2));

			// getKey
			allowing(values).getKey(0);
			will(returnValue(0));
			allowing(values).getKey(1);
			will(returnValue(1));
			allowing(values).getKey(2);
			will(returnValue(2));
	    }});
    }

	//Test cumulative percentage calculation for all values
	@Test 
    public void getCumulativePercentages_ValidComputation() {
    	KeyedValues result = DataUtilities.getCumulativePercentages(values);
    	
    	assertEquals("Cumulative percentage for key 0 should be 0.3125", 
            0.3125, result.getValue(0).doubleValue(), 0.0001);
    	assertEquals("Cumulative percentage for key 1 should be 0.875", 
            0.875, result.getValue(1).doubleValue(), 0.0001);
    	assertEquals("Cumulative percentage for key 2 should be 1.0", 
            1.0, result.getValue(2).doubleValue(), 0.0001);
    }

	// Test that the final cumulative percentage is 1.0
	@Test
    public void getCumulativePercentages_FinalValueIsOne() {
    	KeyedValues result = DataUtilities.getCumulativePercentages(values);
		assertEquals("Final cumulative percentage should be 1.0", 
            1.0, result.getValue(result.getKey(result.getKeys().size() - 1)).doubleValue(), 0.0001);
    }
	
	// Test for a null input (should throw IllegalArgumentException)
	@Test(expected = IllegalArgumentException.class)
	public void getCumulativePercentages_NullInput() {
		DataUtilities.getCumulativePercentages(null);
	}
}
