/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.server.model;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.List;

/**
 * Class represents model of application. It has methods to perform convert of
 given Roman numerals to Arabic numerals. Also it provides correctness validation 
 of input data. Results of convert are stored in list of Integers. 
 * @version 2.0
 * @author Patryk Gregorczuk
 */
public class Converter {
    
    /**
     * Private field that holds list of Strings accepted to conversion by 
     * <code>RomanNumeralsValidator</code> class.
     */ 
    private final List<String> romanNumerals;
    /**
     * Private field that holds list of Integers which respresent result of conversion.
     */ 
    private final List<Integer> arabicNumerals;
    
    /**
     * Private field that holds map used for converting letter to number.
     */ 
    private final Map numeralsMap;
    
    /**
     * Constructor of this class. Initializes internal containers.
     */           
    public Converter()
    {
        romanNumerals = new ArrayList();
        arabicNumerals = new ArrayList();
        
        numeralsMap = new HashMap();
        
        numeralsMap.put('I', 1);
        numeralsMap.put('V', 5);
        numeralsMap.put('X', 10);
        numeralsMap.put('L', 50);
        numeralsMap.put('C', 100);
        numeralsMap.put('D', 500);
        numeralsMap.put('M', 1000);  
    }
    
    /**
     * @return Method returns result of conversion - Arabic numerals as a list of Integers.
     */
    public List<Integer> getResult()
    {
        return arabicNumerals;
    }
    
    /**
     * @return Method returns input data after validation - Roman numerals as a list of Strings.
     */
    public List<String> getRomanNumerals()
    {
        return romanNumerals;
    }
    
    /**
     * Method begins conversion. It reads Roman numerals from List held in model 
     * and pass them one by one to converting method.
     */
    public void convert()
    {     
        //Converting roman numerals one by one using lamda expression
        romanNumerals.forEach((romanNumeral) -> {
            this.convertRomanNumeralToArabic(romanNumeral);
        });
    }
    
    /**
     * Method converts given string that represents correct Roman numeral to
     * int which represents Roman numeral value as Arabic numeral 
     * and puts that int to list of Integers.
     * @param romanNumeral the string that represents correct Roman numeral.
     */
    private void convertRomanNumeralToArabic(String romanNumeral)
    {
        //Variable to store result of single Roman numeral convert.
        int arabicNumeral = 0;
        
        //Algorithm is checking letter by letter from right side of the string.
        char letterFromRomanNumeral = romanNumeral.charAt(romanNumeral.length() - 1);
        
        //Value of each letter is being assigned to variable using map.
        int arabicValueOfLetter = (int)numeralsMap.get(letterFromRomanNumeral);
        
        //Storing previous value is necessary to define if we add or subtract.
        int previousValue = arabicValueOfLetter;

        for(int i = romanNumeral.length() - 1; i >= 0; --i)
        {
            letterFromRomanNumeral = romanNumeral.charAt(i);
            arabicValueOfLetter = (int)numeralsMap.get(letterFromRomanNumeral);

            if(arabicValueOfLetter >= previousValue)
                arabicNumeral += arabicValueOfLetter;
            else
                arabicNumeral -= arabicValueOfLetter;       

            previousValue = arabicValueOfLetter;
        }
        
        //When loop ends converted value is being put to the container.
        arabicNumerals.add(arabicNumeral);
    }
    
    /**
     * Method starts validation process of incoming data and if they are correct
     * puts them to inner containers.
     * @param inputData the list of data that is going to be converted.
     * @throws IncorrectDataException If data were not validated correctly.
     */    
    public void receiveData(List<String> inputData)
        throws IncorrectDataException
    {
        if(inputData != null)
        {
            for (String singleInputData : inputData) 
            {
                String singleUpperCaseInputData = singleInputData.toUpperCase();

                if (validateIncomingData(singleUpperCaseInputData)) 
                    this.romanNumerals.add(singleUpperCaseInputData);
                else
                    throw new IncorrectDataException(singleInputData);
            }
        }
        else
            throw new IncorrectDataException("Input list was NULL!");
    }
    
    /**
     * Method checks given string if it represents correct Roman numeral.
     * @param stringToValidate the string which will be checked.
     * @return <b>true</b> if stringToValidate is correct.
     * <b>false</b> if stringToValidate is empty or incorrect.
     */ 
    private boolean validateIncomingData(String stringToValidate)
    {
        RomanNumeralsValidator romanNumeralsValidator = new RomanNumeralsValidator();
        return romanNumeralsValidator.validate(stringToValidate);
    }
    
    /**
     * This method clears inner containers.
     */ 
    public void clearData()
    {
        romanNumerals.clear();
        arabicNumerals.clear();
    }
}
