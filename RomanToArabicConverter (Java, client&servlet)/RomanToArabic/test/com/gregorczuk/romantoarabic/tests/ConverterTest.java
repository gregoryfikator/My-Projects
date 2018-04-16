/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.tests;

import com.gregorczuk.romantoarabic.server.model.Converter;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import org.junit.*;

import static org.junit.Assert.*;
/**
 * This class provides tests for public methods of <code>Converter</code> class. 
 * It contains instance of Converter class and fields with lists of input data 
 * and expected results. 
 * @author Patryk Gregorczuk
 * @version 2.0
 */
public class ConverterTest {
    
    Converter converter;
    
    List<String> inputDataList;
    List<String> expectedResultList;
    List<Integer> expectedArabicResultList;    

    /**
    * Creates instantion of <code>Converter</code> and initializes fields for testing 
    * with correct example values. Method is being called before performing each unit test.
    */
    @Before
    public void setUpClass()
    {
        converter = new Converter();
        
        inputDataList = new ArrayList();
        inputDataList.add("XII");
        inputDataList.add("MMXVII");
        inputDataList.add("DCLXVI");
        
        expectedResultList = new ArrayList();
        expectedResultList.add("XII");
        expectedResultList.add("MMXVII");
        expectedResultList.add("DCLXVI");
        
        expectedArabicResultList = new ArrayList();  
        expectedArabicResultList.add(12);
        expectedArabicResultList.add(2017);
        expectedArabicResultList.add(666);        
    }
    
   /**
    * Provides test for <code>receiveData</code> method with <u>correct input</u>.
    * Passed input data is being compared with expected result by assertEquals.
    * @throws Exception Needs to be thrown as tested method also throws it.
    */
    @Test
    public void testReceiveDataWithCorrectInputResultShouldEquals() throws Exception
    {       
        converter.receiveData(inputDataList);
        assertEquals(converter.getRomanNumerals(), expectedResultList);
    }
    
   /**
    * Provides test for <code>receiveData</code> method with <u>correct <b>empty</b> input</u>.
    * Passed input data is being compared with expected result by assertEquals.
    * @throws Exception Needs to be thrown as tested method also throws it.
    */
    @Test
    public void testReceiveDataWithEmptyInputResultShouldEquals() throws Exception
    {    
        //Clearing fields initialized in setUpClass.
        inputDataList.clear();
        expectedResultList.clear();
        
        converter.receiveData(inputDataList);
        assertEquals(converter.getRomanNumerals(), expectedResultList);
    }
    
   /**
    * Provides test for <code>receiveData</code> method with <u>incorrect input</u>.
    * Passed input data should cause an exception. 
    * Test will be successful when excption occures.
    * @throws Exception Needs to be thrown as tested method also throws it.
    */
    @Test(expected = Exception.class)
    public void testReceiveDataWithIncorrectInputExceptionMustBeThrown() throws Exception
    {    
        inputDataList.add("ZZZZ"); // <- bad input
        converter.receiveData(inputDataList);
    }
    
   /**
    * Provides test for <code>receiveData</code> method with <u>null input</u>.
    * Passed null object of input data should cause an exception. 
    * Test will be successful when excption occures.
    * @throws Exception Needs to be thrown as tested method also throws it.
    */
    @Test(expected = Exception.class)
    public void testReceiveDataWithNullInputObjectExceptionMustBeThrown() throws Exception
    {    
        inputDataList = null; // Basically, null inputDataList never occurs.
        converter.receiveData(inputDataList);
    }
    
   /**
    * Provides test for <code>receiveData</code> method with <u>correct input 
    * that contains lower case roman numerals</u>.
    * Passed input data is being compared with expected result by assertEquals.
    * @throws Exception Needs to be thrown as tested method also throws it.
    */
    @Test
    public void testReceiveDataWithCorrectLowerCaseInputResultShouldEquals() throws Exception
    {
        inputDataList.add("xlv");        
        expectedResultList.add("XLV");
            
        converter.receiveData(inputDataList);
        assertEquals(converter.getRomanNumerals(), expectedResultList);
    }

   /**
    * Provides test for <code>convert</code> method.
    * Test uses mechanism of relfection in order to access and set private field of 
    * Converter`s class object. Result of conversion can be accessed by <code>getResult</code> 
    * method and be asserted with expected.
    * @throws Exception If specified field does not exist.
    */
    @Test
    public void testConvertResultShouldEquals() throws Exception
    {        
        //Setting private field of Converter class instance.
        Field fieldRomanNumerals = Converter.class.getDeclaredField("romanNumerals");
        fieldRomanNumerals.setAccessible(true);
        fieldRomanNumerals.set(converter, inputDataList);
        
        converter.convert();
        
        assertEquals(converter.getResult(), expectedArabicResultList);
    }
    
   /**
    * Provides test for <code>clearData</code> method.
    * Test uses mechanism of relfection in order to access and set private fields of 
    * Converter`s class object. Tested method clears private fields and result
    * is being asserted with empty lists.
    * @throws Exception If specified field does not exist.
    */
    @Test
    public void testClearDataFromInternalCollectionsOfConverterListsShouldBeClear() throws Exception
    {        
        //Setting private field of Converter class instance.
        Field fieldRomanNumerals = Converter.class.getDeclaredField("romanNumerals");
        fieldRomanNumerals.setAccessible(true);
        fieldRomanNumerals.set(converter, inputDataList);
        
        //Setting private field of Converter class instance.
        Field fieldArabicNumerals = Converter.class.getDeclaredField("arabicNumerals");
        fieldArabicNumerals.setAccessible(true);
        fieldArabicNumerals.set(converter, expectedArabicResultList);
        
        expectedResultList.clear();
        expectedArabicResultList.clear();
        
        converter.clearData();
        
        assertEquals(converter.getRomanNumerals(), expectedResultList);
        assertEquals(converter.getResult(), expectedArabicResultList);
    }
}