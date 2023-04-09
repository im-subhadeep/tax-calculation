#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct employee
{
    char employee_id[10], employee_name1[15], employee_name2[15];
    double total_taxable_income;
    double taxable_income_after_deduction;
    double investments;
    double income_from_bank_land;
    double total_tax_payable;
    double total_income;
    double total_income_after_deduction;
    double total_income_tax;
    double income_tax_on_bank_and_land;

} empl;

int main()
{
    int n;
    printf("\n\nEnter The Number of Employees: ");
    scanf("%d", &n);
    empl emp[n];
    FILE *ftr = fopen("Taxes.csv", "w+");
    fprintf(ftr, "Employee Id,Employee Name,Enter Total Taxable Income,Enter Investments,Enter Taxable Income After Deduction,Enter Income from Bank Interest and Land,Total Tax Payable");

    // Input

    printf("\n\n--Enter your details--\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("\n");
        printf("Employee Id: ");
        scanf("%s", emp[i].employee_id);
        printf("Employee Name: ");
        scanf("%s", emp[i].employee_name1);
        scanf("%s", emp[i].employee_name2);

        printf("Enter Total Taxable Income: ");
        scanf("%lf", &emp[i].total_taxable_income);

        printf("Enter Investments: ");
        scanf("%lf", &emp[i].investments);

        printf("Enter Taxable Income After Deduction: ");
        scanf("%lf", &emp[i].taxable_income_after_deduction);

        printf("Enter Income from Bank Interest and Land: ");
        scanf("%lf", &emp[i].income_from_bank_land);
    }

    // Calculation
    for (int i = 0; i < n; i++)
    {
        emp[i].total_income = emp[i].total_taxable_income - emp[i].investments;
        emp[i].total_income_after_deduction = emp[i].total_income - emp[i].taxable_income_after_deduction;
        emp[i].total_income_tax = 0;

        if (emp[i].total_income_after_deduction > 0)
        {
            if (emp[i].total_income_after_deduction <= 250000)
            {
                emp[i].total_income_tax = 0;
            }
            else if (emp[i].total_income_after_deduction > 250000 && emp[i].total_income_after_deduction <= 500000)
            {
                emp[i].total_income_tax = (emp[i].total_income_after_deduction - 250000) * 0.05;
            }
            else if (emp[i].total_income_after_deduction > 500000 && emp[i].total_income_after_deduction <= 1000000)
            {
                emp[i].total_income_tax = 12500 + (emp[i].total_income_after_deduction - 500000) * 0.2;
            }
            else
            {
                emp[i].total_income_tax = 112500 + (emp[i].total_income_after_deduction - 1000000) * 0.3;
            }
        }

        emp[i].income_tax_on_bank_and_land = emp[i].income_from_bank_land * 0.1;
        emp[i].total_tax_payable = emp[i].total_income_tax + emp[i].income_tax_on_bank_and_land;
    }

    // Output

    for (int i = 0; i < n; i++)
    {
        fprintf(ftr, "\n%s", emp[i].employee_id);
        fprintf(ftr, ",%s %s", emp[i].employee_name1, emp[i].employee_name2);
        fprintf(ftr, ",%.2lf", emp[i].total_taxable_income);
        fprintf(ftr, ",%.2f", emp[i].investments);
        fprintf(ftr, ",%.2lf", emp[i].taxable_income_after_deduction);
        fprintf(ftr, ",%.2lf", emp[i].income_from_bank_land);
        fprintf(ftr, ",%.2lf", emp[i].total_tax_payable);
    }

    // Search facility

    while (1)
    {
        int x;
        printf("\n\n1.Search\n2.Generate a report\n3.Exit\n\n:");
        scanf("%d", &x);
        char k[10];
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum = sum + emp[i].total_tax_payable;
        }

        switch (x)
        {
        case 1:
            printf("\n\nEmployee Id: ");
            scanf("%s", k);
            for (int i = 0; i < n; i++)
            {
                if (strcmp(emp[i].employee_id, k) == 0)
                {
                    printf("\n\nEmployee Id: %s\n", emp[i].employee_id);
                    printf("Employee Name: %s %s\n", emp[i].employee_name1, emp[i].employee_name2);
                    printf("Total Tax Payable: %.2lf\n", emp[i].total_tax_payable);
                }
            }
            break;
        case 2:
            printf("\n\nTotal number of employees: %d\n", n);
            printf("Total tax payable: %d\n", sum);
            break;
        case 3:

            exit(0);
        }
    }

    return 0;
}