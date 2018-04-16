/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.tests;

import com.gregorczuk.romantoarabic.server.model.RomanNumeralsValidator;
import org.junit.*;
import static org.junit.Assert.*;

/**
 * Class provides tests for <code>RomanNumeralsValidator</code>.
 * @author Patryk Gregorczuk
 * @version 2.0
 */
public class RomanNumeralsValidatorTest {
    
    RomanNumeralsValidator romanNumeralsValidator;
    
   /**
    * Creates instantion of <code>RomanNumeralsValidator</code>.
    * Method is being called before performing each unit test.
    */
    @Before
    public void setUpClass()
    {
        romanNumeralsValidator = new RomanNumeralsValidator();
    }
    
   /**
    * Provides test for <code>validate</code> method with <u>arabic numeral as input</u>.
    * Assertion should be false.
    */
    @Test
    public void testValidateWithArabicNumeralAsInputShouldBeFalse()
    {    
        assertFalse(romanNumeralsValidator.validate("123"));        
    }
    
   /**
    * Provides test for <code>validate</code> method with <u>empty string as input</u>.
    * Assertion should be false.
    */
    @Test
    public void testValidateWithEmptyStringAsInputShouldBeFalse()
    {
       assertFalse(romanNumeralsValidator.validate("")); 
    }
    
   /**
    * Provides test for <code>validate</code> method with <u>incorrect roman numeral as input</u>.
    * Assertion should be false.
    */
    @Test
    public void testValidateWithIncorrectRomanNumeralAsInputShouldBeFalse()
    {
       assertFalse(romanNumeralsValidator.validate("IIIX")); 
    }
    
    /**
    * Provides test for <code>validate</code> method with <u>correct roman numeral as input</u>.
    * Assertion should be true.
    */
    @Test
    public void testValidateWithCorrectRomanNumeralAsInputStringShouldBeTrue()
    {
       assertTrue(romanNumeralsValidator.validate("CLXI")); 
    }
}