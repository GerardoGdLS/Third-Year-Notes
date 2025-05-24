package org.jfree.data.test;
import static org.junit.Assert.*;
import org.jfree.data.Range;
import org.junit.*;
public class Range_IntersectsTest {
    private Range exampleRange;
    @Before
    public void setUp() {
        exampleRange = new Range(-1, 1);
    }
    @Test
    public void testIntersectAtUpper() {
        assertTrue("Range(-1,1) should intersect with (0,1)", exampleRange.intersects(0,1));
    }
    @Test
    public void testIntersectAtLower() {
        assertTrue("Range(-1,1) should intersect with (-1,0)", exampleRange.intersects(-1,0));
    }
    @Test
    public void testIntersectOutside() {
        assertFalse("Range(-1,1) should not intersect with (2, 4)", exampleRange.intersects(2,4));
    }
    @Test
    public void testIntersectUB() {
        assertTrue("Range(-1,1) should intersect with (1, 3)", exampleRange.intersects(1, 3));
    }
    @Test
    public void testIntersectBUB() {
        assertTrue("Range(-1,1) should intersect with (-2, 0)", exampleRange.intersects(-2, 0));
    }
    @Test
    public void testIntersectNOM() {
        assertTrue("Range(-1,1) should intersect with (-0.5, 0.5)", exampleRange.intersects(-0.5, 0.5));
    }
    @Test
    public void testIntersectALB() {
        assertTrue("Range(-1,1) should intersect with (0,2)", exampleRange.intersects(0, 2));
    }
    @Test
    public void testIntersectLB() {
        assertTrue("Range(-1,1) should intersect with (-3, -1)", exampleRange.intersects(-3, -1));
    }
}