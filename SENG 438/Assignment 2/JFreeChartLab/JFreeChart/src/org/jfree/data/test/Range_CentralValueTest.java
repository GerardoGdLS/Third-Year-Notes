package org.jfree.data.test;
import static org.junit.Assert.*;
import org.jfree.data.Range;
import org.junit.*;
public class Range_CentralValueTest {
    private Range exampleRange;
    @Before
    public void setUp() {
        exampleRange = new Range(-1, 1);
    }
    @Test
    public void centralValueShouldBeZero() {
        assertEquals("The central value of -1 and 1 should be 0",
        0, exampleRange.getCentralValue(), .000000001d);
    }
    @Test
    public void testcentralValuePositive() {
        Range newRange = new Range(1, 5);
        assertEquals("The central value of 1 and 5 should be 3", 3, newRange.getCentralValue(), .000000001d);
    }
    @Test
    public void testcentralValueNegative() {
        Range newRange = new Range (-5, -1);
        assertEquals("The central value of -4 and -1 should be -3", -3, newRange.getCentralValue(), .000000001d);
    }
    @Test
    public void testcentralValueZeroCrossing() {
        Range newRange = new Range (-2, 4);
        assertEquals("The central value of -2 and 4 should be 1", 1, newRange.getCentralValue(), .000000001d);
    }
    @Test
    public void testcentralValueInfinite() {
        Range newRange = new Range (Double.NEGATIVE_INFINITY, 2000);
        assertEquals("The central value of infinity should be infinity", Double.POSITIVE_INFINITY, newRange.getCentralValue(), .000000001d);
    }
    @Test
    public void testcentralValueNAN() {
        Range newRange = new Range(Double.NaN, 10);
        assertTrue("The central value should return NaN when one bound is NaN", Double.isNaN(newRange.getCentralValue()));
    }
}