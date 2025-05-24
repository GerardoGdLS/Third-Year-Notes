package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.DataUtilities;
import org.junit.*;
import java.util.Arrays;

public class DataUtilities_createNumberArray2DTest {

    @BeforeClass 
    public static void setUpBeforeClass() throws Exception {
    }

    @Before
    public void setUp() throws Exception { }

    // Converts a 2D array of double primitives to Number objects
    @Test
    public void testCreateNumberArray2D_ValidInput() {
        double[][] input = {
            {1.5, 2.5, 3.5},
            {4.5, 5.5, 6.5}
        };
        Number[][] expected = {
            {1.5, 2.5, 3.5},
            {4.5, 5.5, 6.5}
        };

        Number[][] result = DataUtilities.createNumberArray2D(input);

        assertTrue("Conversion of double[][] to Number[][] failed.", Arrays.deepEquals(expected, result));
    }

    //  Null input should throw IllegalArgumentException
    @Test(expected = IllegalArgumentException.class)
    public void testCreateNumberArray2D_NullInput() {
        DataUtilities.createNumberArray2D(null);
    }

    //  Method must return a 2D array of Number objects
    @Test
    public void testCreateNumberArray2D_ReturnsNumberArray() {
        double[][] input = {
            {4.2, 5.6},
            {7.8, 9.1}
        };
        Number[][] result = DataUtilities.createNumberArray2D(input);

        assertNotNull("Result should not be null.", result);
        assertEquals("Result should have the same row count as input.", input.length, result.length);
        
        for (int i = 0; i < input.length; i++) {
            assertEquals("Row " + i + " should have the same column count.", input[i].length, result[i].length);
            for (int j = 0; j < input[i].length; j++) {
                assertTrue("Each element should be an instance of Number.", result[i][j] instanceof Number);
            }
        }
    }

    //  Method must handle an empty 2D array correctly
    @Test
    public void testCreateNumberArray2D_EmptyArray() {
        double[][] input = new double[0][];
        Number[][] result = DataUtilities.createNumberArray2D(input);

        assertNotNull("Result should not be null.", result);
        assertEquals("Empty 2D input should return an empty 2D Number array.", 0, result.length);
    }


    @After
    public void tearDown() throws Exception {
    }

    @AfterClass
    public static void tearDownAfterClass() throws Exception {
    }
}
