/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.server.model;

/**
 * Provides method to check if given string is correct Roman numeral by comparing it
 * with prepared regular expression.
 * @version 2.0
 * @author Patryk Gregorczuk
 */
public class RomanNumeralsValidator {
    
    /**
     * Regular expression that represents each correct Roman numeral from 1 to 3999.
     */
    private final String regex = "M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})";
    
    /**
     * Default constructor of this class.
     */
    public RomanNumeralsValidator()
    {
    }
    
    /**
     * Method checks given string if it represents correct Roman numeral.
     * @param stringToValidate the string which will be checked. 
     * @return <b>true</b> if stringToValidate is correct.
     * <b>false</b> if stringToValidate is empty or incorrect.
     */
    public boolean validate(String stringToValidate)
    {        
        return !stringToValidate.isEmpty() 
                && stringToValidate.matches(this.regex);
    }
}
