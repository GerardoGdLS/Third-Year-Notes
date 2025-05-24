package org.jfree.data.test;
import static org.junit.Assert.*;
import org.jfree.data.Range;
import org.junit.*;
public class Range_CombinedTest {
    private Range exampleRange;
    @Before
    public void setUp() {
        exampleRange = new Range(-1, 1);
    }
    @Test
    public void testCombineBothNull() {
        assertNull(Range.combine(null, null));
    }
    @Test
    public void testCombineSecondRangeNull() {
        assertEquals(exampleRange, Range.combine(exampleRange, null));
    }
    @Test
    public void testCombineFirstRangeNull() {
        assertEquals(exampleRange, Range.combine(null, exampleRange));
    }
    @Test
    public void testCombineFirstOverlapSecond() {
    	//BUG Test fails although it should combine to a new range of (-1, 5)
        Range r2 = new Range(0, 5);
        assertEquals(new Range(-1, 5), Range.combine(exampleRange, r2));
    }
    @Test
    public void testCombineSecondOverlapFirst() {
        Range r2 = new Range(-2, 5);
        assertEquals(new Range(-2, 5), Range.combine(exampleRange, r2));
    }
    @Test
    public void testCombineOneRangeFullyContainsOther() {
        Range r2 = new Range(-3, 8);
        assertEquals(new Range(-3, 8), Range.combine(exampleRange, r2));
    }
    @Test
    public void testCombineRangesAreEqual() {
        Range r2 = new Range(-1, 1);
        assertEquals(new Range(-1, 1), Range.combine(exampleRange, r2));
    }
    @Test
    public void testCombineDisjointAndCombine() {
        Range r2 = new Range(-3, -2);
        assertEquals(new Range(-3, 1), Range.combine(exampleRange, r2));
    }
    @Test
    public void testCombineDisjointDoNotCombine() {
    	//Test should fail as it cannot combine the two values
        Range r2 = new Range(3, 6);
        assertEquals(exampleRange, Range.combine(exampleRange, r2));
    }
}