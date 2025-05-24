package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.Range;
import org.junit.*;

public class Range_constrainTest {
    private Range exampleRange;

    @Before
    public void setUp() {
        exampleRange = new Range(-1, 1);
    }

    @Test
    public void testConstrainInsideRange() {
        assertEquals(1, exampleRange.constrain(3), .000000001d);
    }

    @Test
    public void testConstrainOnLowerBound() {
        assertEquals(-1, exampleRange.constrain(-1), .000000001d);
    }

    @Test
    public void testConstrainOnUpperBound() {
        assertEquals(1, exampleRange.constrain(1), .000000001d);
    }

    @Test
    public void testConstrainBelowLowerBound() {
        assertEquals(-1, exampleRange.constrain(-5), .000000001d);
    }

    @Test
    public void testConstrainAboveUpperBound() {
        assertEquals(1, exampleRange.constrain(5), .000000001d);
    }
}
