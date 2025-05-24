package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.DataUtilities;
import org.junit.*;

public class DataUtilities_createNumberArrayTest{

    @BeforeClass 
    public static void setUpBeforeClass() throws Exception {
    }

    @Before
    public void setUp() throws Exception { }

    // converts an array of double primitives to Number objects
    @Test
    public void testCreateNumberArray_ValidInput() {
        double[] input = {1.5, 2.5, 3.5};
        Number[] expected = {1.5, 2.5, 3.5};

        Number[] result = DataUtilities.createNumberArray(input);

        assertArrayEquals("Conversion of double[] to Number[] failed.", expected, result);
    }

    //  Null input should throw IllegalArgumentException
    @Test(expected = IllegalArgumentException.class)
    public void testCreateNumberArray_NullInput() {
        DataUtilities.createNumberArray(null);
    }

    // Method must handle an empty array correctly
    @Test
    public void testCreateNumberArray_EmptyArray() {
        double[] input = {};
        Number[] result = DataUtilities.createNumberArray(input);

        assertNotNull("Result should not be null.", result);
        assertEquals("Empty input should return an empty array.", 0, result.length);
    }

    // Method must return an array of Number objects
    @Test
    public void testCreateNumberArray_ReturnsNumberArray() {
        double[] input = {4.2, 5.6, 7.8};
        Number[] result = DataUtilities.createNumberArray(input);

        assertNotNull("Result should not be null.", result);
        assertEquals("Result should have the same length as input.", input.length, result.length);
        
        for (Number n : result) {
            assertTrue("Each element should be an instance of Number.", n instanceof Number);
        }
    }
    
    @After
    public void tearDown() throws Exception {
    }

    @AfterClass
    public static void tearDownAfterClass() throws Exception {
    }
}
