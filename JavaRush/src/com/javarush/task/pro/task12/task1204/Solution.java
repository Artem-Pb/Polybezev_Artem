package com.javarush.task.pro.task12.task1204;

/* 
Плата по счетам
*/

public class Solution {
    public static Integer balance = Integer.MAX_VALUE;

    public static void main(String[] args) {
        String bill = "1234567890";

        System.out.println("Текущий баланс : " + balance);
        processPayment(bill);
        System.out.println("Текущий баланс : " + balance);
    }

    public static void processPayment(String bill) {
        balance -= Integer.parseInt(bill);
    }
}

//if ((a > zero || a == posInf || a == negInf)
//                && (b == zero
//                || (b >= zero && b != posInf)
//                || (b != negInf && b == 0))) {
//            posInf = Double.valueOf(a) / Double.valueOf(b);
//        } else if ((a < zero || a == negInf || a == posInf)
//                && ((b >= zero && b != posInf)
//                || (b == zero && b != negInf))) {
//            System.out.println(negInf);
//        } else if ((a == zero && b == zero)
//                || (a == nan || b == nan)
//                || (a == posInf && b == posInf)
//                || (a == posInf && b == negInf)
//                || (a == negInf && b == posInf)
//                || (a == negInf && b == negInf)) {
//            System.out.println(nan);
//        }
//    }
//}
