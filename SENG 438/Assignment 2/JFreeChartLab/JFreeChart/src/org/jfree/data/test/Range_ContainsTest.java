package org.jfree.data.test;

import static org.junit.Assert.*;
import org.jfree.data.Range;
import org.junit.*;

public class Range_ContainsTest {
    private Range exampleRange;

    @Before
    public void setUp() {
        exampleRange = new Range(-1, 1);
    }

    @Test
    public void testContainsInsideBounds() {
        assertTrue("Range contains value 0", exampleRange.contains(0));
    }

    @Test
    public void testContainsJustInsideBounds() {
        assertTrue("Range contains value 0.9", exampleRange.contains(0.9));
    }

    @Test
    public void testContainsOnLeftBoundary() {
        assertTrue("Range contains value -1", exampleRange.contains(-1));
    }

    @Test
    public void testContainsOnRightBoundary() {
        assertTrue("Range contains value 1", exampleRange.contains(1));
    }

    @Test
    public void testContainsOutsideBoundsFarLeft() {
        assertFalse("Range should not contain -20", exampleRange.contains(-20));
    }

    @Test
    public void testContainsJustOutsideBoundsLeft() {
        assertFalse("Range should not contain -2", exampleRange.contains(-2));
    }

    @Test
    public void testContainsOutsideBoundsFarRight() {
        assertFalse("Range should not contain 20", exampleRange.contains(20));
    }

    @Test
    public void testContainsJustOutsideBoundsRight() {
        assertFalse("Range should not contain 2", exampleRange.contains(2));
    }
}
