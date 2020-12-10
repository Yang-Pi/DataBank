Use Sber
Go

--0
Alter Procedure SignUp
			@Name As varchar(30), @Sername As varchar(30), @FatherName varchar(30),
			@PasportSeries As int, @PasportNumber As int, @Birthday As date, @PhoneNumber As varchar(19)
As
Insert Into Pasport_data (number, series) Values (@PasportNumber, @PasportSeries);
Insert Into Client (name, sername, father_name, birthday, phone_number, pasport_data_id)
			Values (@Name, @Sername, @FatherName, @Birthday, @PhoneNumber, 
			(Select pasport_data_id From Pasport_data Where number = @PasportNumber And series = @PasportSeries));
Go

Exec SignUp 'Yaroslav', 'Pylaev', 'Sergeevich', 1111, 123456, '2000-12-23', '89518102252';
Go

--
Alter Procedure GetClientInfo
	@ClientPasportSeries As int, @ClientPasportNumber As int
As
Select client_id, sername, name, father_name, Pasport.series, Pasport.number, birthday, phone_number From Client 
Join Pasport_data Pasport 
On Client.pasport_data_id = Pasport.pasport_data_id
	And Pasport.series = @ClientPasportSeries
	And Pasport.number = @ClientPasportNumber
Go

Exec GetClientInfo 1111, 123456;
Go

--1
Alter Procedure ArrangeCard
	@ClientId As int, @Number As varchar(19), @Validity As varchar(5), @CVV As varchar(3), @PIN As varchar(4)
As
Insert Into Card_secret_data (cvv_code, pin_code) Values (@CVV, @PIN);
Declare @StartBalance As int;
Set @StartBalance = 100;
Insert Into Card (client_id, number, validity, balance, secret_data_id) 
Values
	(@ClientId, @Number, @Validity, 0, (Select Min(secret_data_id) From Card_secret_data Where cvv_code = @CVV And pin_code = @PIN));
Select Client.name, Client.sername, Card.number, Card.validity, Card_secret_data.cvv_code, Card.balance From Client
	Join Card On Card.client_id = Client.client_id
	Join Card_secret_data On Card.secret_data_id = Card_secret_data.secret_data_id
	Where Card.number = @Number;
Go

Exec ArrangeCard 36, 'test_number2', '06/21', '111', '0000';
Go

--
Alter Procedure GetCardSecretData --при личной явке клиента в отдление банка
	@PasportSeries As int, @PasportNumber As int, @CardNumber As varchar(19)
As
Select Card.number, Card.validity, Card_secret_data.cvv_code, Card_secret_data.pin_code From Card_secret_data
	Join Card On Card_secret_data.secret_data_id = Card.secret_data_id
	Join Client On Card.client_id = Client.client_id
	Join Pasport_data On Client.pasport_data_id = Pasport_data.pasport_data_id
		And Pasport_data.series = @PasportSeries
		And Pasport_data.number = @PasportNumber;
Go

--2
Create Procedure CreateDepositTarif
	@Rate As float, @MinDeposit As int
As
	Insert Into Deposit_tarif(rate, min_deposit) Values (@Rate, @MinDeposit);
Go

Exec CreateDepositTarif 5.5, 100000;

Alter Procedure UpdateDepositTarif
	@TarifId As int, @Rate As float, @MinDeposit As int
As
Update Deposit_tarif
Set rate = @Rate, min_deposit = @MinDeposit
Where deposit_tarif_id = @TarifId;
Go

Exec UpdateDepositTarif 1, 5.7, 100000
Go

--
Alter Procedure OpenAccount
	@ClientId As int, @Tarif_id As int, @Number As varchar(16), @Deposit As int, @Closing_date As date
As
Insert Into Account(client_id, deposit_tarif_id, number, deposit, closing_date) Values (@ClientId, @Tarif_id, @Number, @Deposit, @Closing_date);
Go

Exec OpenAccount 36, 1, 'test_number', 200000, '2021-12-1';
Go

--3
Create Procedure GetCardBalance
	@CardNumber As varchar(19), @PinCode As varchar(4)
As
Select balance From Card
Join Card_secret_data On Card.secret_data_id = Card_secret_data.secret_data_id
Where number = @CardNumber And pin_code = @PinCode;
Go

Execute GetCardBalance 'test_number', '0000';
Go

--
Alter Procedure GetAccountBalance
	@PasportSeries As int, @PasportNumber As int, @AccountNumber As varchar(16)
As
Select Account.number, deposit, accumulation, closing_date From Account
	Join Client On Account.client_id = Client.client_id
	Join Pasport_data On Client.pasport_data_id = Pasport_data.pasport_data_id
	Where Pasport_data.series = @PasportSeries And Pasport_data.number = @PasportNumber And Account.number = @AccountNumber
Go

--4
Create Procedure WithdrawMoneyFromCard
	@CardNumber As varchar(19), @PinCode As varchar(4), @Sum As int
As
If @Sum < (Select balance From Card Where number = @CardNumber) And 
			@PinCode = (Select pin_code From Card 
									Join Card_secret_data On Card.secret_data_id = Card_secret_data.secret_data_id 
									Where Card.number = @CardNumber) 
Update Card Set balance = balance - @Sum Where number = @CardNumber;
Go

Execute WithdrawMoneyFromCard 'test_number', '0000', 100;
Go

--5
Alter Procedure TopUpCardBalance
	@CardNumber As varchar(19), @Sum As int
As
Update Card Set balance = balance + @Sum Where number = @CardNumber;

--
Create Procedure TopUpDeposit
	@PasportSeries As int, @PasportNumber As int, @AccountNumber As varchar(16), @Sum As int
As
Update Account Set deposit  += @Sum 
	From Account
	Join Client On Account.client_id = Client.client_id
	Where Exists (Select Pasport_data.pasport_data_id From Pasport_data 
	Where series = @PasportSeries 
		And number = @PasportNumber
		And Pasport_data.pasport_data_id = Client.pasport_data_id);
Go

--6
Alter Procedure WithdrawAccountAccumulation
	@PasportSeries As int, @PasportNumber As int, @AccountNumber As varchar(16), @CardNumber As varchar(19)
As
Declare @Accumulation As int;
Set @Accumulation = (Select accumulation	From Account
		Join Client On Account.client_id = Client.client_id
		Where Exists (Select Pasport_data.pasport_data_id From Pasport_data 
			Where series = @PasportSeries 
				And number = @PasportNumber
				And Pasport_data.pasport_data_id = Client.pasport_data_id)
			And Account.number = @AccountNumber);
If @Accumulation > 0
	Exec TopUpCardBalance @CardNumber, @Accumulation;
	Update Account Set accumulation = 0;
Go

--7
Create Procedure MoveMoneyFromCardToCard
	@FirstCardNumber As varchar(19), @FirstCardPinCode As varchar(4), @SecondCardNumber As varchar(19), @Sum As int
As
	Exec WithdrawMoneyFromCard @FirstCardNumber, @FirstCardPinCode, @Sum;
	Exec TopUpCardBalance @SecondCardNumber, @Sum;
Go

Exec MoveMoneyFromCardToCard 'test_number', '0000', 'test_number2', 500;
Go

--8
Create Procedure CreateCreditTarif
	@Rate As float, @MaxSum As int
As
Insert Into Credit_tarif(rate, max_credit) Values (@Rate, @MaxSum);
Go

Exec CreateCreditTarif 8.8, 3000000;
Go
--
Create Procedure UpdateCreditTarif
	@TarifId As int, @Rate As float, @MaxSum As int
As
Update Credit_tarif
Set rate = @Rate, max_credit = @MaxSum
Where credit_tarif_id = @TarifId;
Go

Exec UpdateCreditTarif 1, 8.5, 3500000
Go

--
Alter Procedure ApplyForCredit
	@ClientId As int, @AvgSalary As int, @Amount As int
As
Insert Into Credit_request (client_id, average_salary, amount, status_id) Values (@ClientId, @AvgSalary, @Amount, 1);
Select Max(request_id), Request_status.name
From Credit_request Join Request_status On Credit_request.status_id = Request_status.status_id 
Where client_id = @ClientId 
Group By Request_status.name;
Go

Execute ApplyForCredit 36, 50000, 2000000;
Go

--
Alter Procedure ConsiderCreditRequest
	@RequestId As int, @EmployeeId As int
As
Update Credit_request Set employee_id = @EmployeeId, status_id = 2 Where @RequestId = request_id;
Go

--
Alter Procedure ApproveCreditRequest
	@RequestId As int, @Time As int, @TarifId As int, @Payment As int, @CreditNumber As varchar(10)
As
if (Select status_id From Credit_request Where @RequestId = request_id) = 1
Begin
	Update Credit_request Set time = @Time, tarif_id = @TarifId, status_id = 3 Where @RequestId = request_id;
	
	Declare @ClientId As int;
	Set @ClientId = (Select client_id From Credit_request Where @RequestId = request_id);
	Declare @Balance As int;
	Set @Balance = (Select amount From Credit_request Where @RequestId = request_id);
	Declare @NextPayment As date;
	Set @NextPayment = DATEADD(m, 1, GETDATE());
	Declare @ClosingDate As date;
	Set @ClosingDate = DATEADD(m, @Time, GETDATE());
	
	Insert Into Credit (number, client_id, credit_tarif_id, payment, balance, next_payment, closing_date)
		Values (@CreditNumber, @ClientId, @TarifId, @Payment, @Balance, @NextPayment, @ClosingDate);
End
Go

Execute ApproveCreditRequest 12, 24, 1, 18000, 'testnumber';
Go

Alter Procedure RefuseCreditRequest
	@RequestId As int
As
Update Credit_request Set status_id = 3 Where request_id = @RequestId
Go

Alter Procedure CheckRequestStatus
	@RequestId As int, @PasportSerise As int, @PasportNumber As int
As
Select request_id, Request_status.name From Credit_request
	Join Request_status On Credit_request.status_id = Request_status.status_id
	Join Client On Credit_request.client_id = Client.client_id
	Join Pasport_data On Client.pasport_data_id = Pasport_data.pasport_data_id And Pasport_data.series = @PasportSerise And Pasport_data.number = @PasportNumber
	Where request_id = @RequestId
Go

--
Alter Procedure PayForCredit
	@CreditNumber As varchar(10), @CardNumber As varchar(19), @CardPinCode As varchar(4)
As
Declare @Payment As int;
Set @Payment = (Select min(min_payment.payment) 
								From (Select payment From Credit Where 'testnumber' = number 
											Union 
											Select balance From Credit Where 'testnumber' = number) min_payment);

If @Payment < (Select balance From Card Where @CardNumber = number) 
	 And @CardPinCode = (Select pin_code From Card 
											 Join Card_secret_data On Card.secret_data_id = Card_secret_data.secret_data_id 
											 Where Card.number = @CardNumber)
Begin
	Exec WithdrawMoneyFromCard @CardNumber, @CardPinCode, @Payment;
	Update Credit Set balance -= payment, next_payment = DATEADD(m, 1, next_payment);
	Select balance, payment, next_payment From Credit Where number = @CreditNumber;
End
Else
	Select 'Недостаточно средств';
Go

Execute TopUpCardBalance 'test_number', 3000;
Execute PayForCredit 'testnumber', 'test_number', '0000';
Go

Create Procedure GetCreditInfo
	@CreditNumber As varchar(10), @PasportSeries As int, @PasportNumber As int
As
Select CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)), 
			 credit_id, Credit.number, balance, payment, next_payment, closing_date 
From Credit
Join Client On Credit.client_id = Client.client_id
Join Pasport_data On Client.pasport_data_id = Pasport_data.pasport_data_id
Where Pasport_data.series = @PasportSeries And Pasport_data.number = @PasportNumber
Go

--9
Alter Trigger ArrangeCardActivity
On Card After Insert
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 4, i.client_id, i.card_id, GETDATE(), i.balance
From Inserted i
Go

Execute SignUp 'Liza', 'Chebunina', 'Nikolaevna', 1111, 234567, '2001-11-08', '';
Execute GetClientInfo 1111, 234567;
Execute ArrangeCard 38, 'test_number2', '12/23', '081', '0000';
Go

--
Alter Trigger AddCardActivity
On Card After Update
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 1, i.client_id, i.card_id, GETDATE(), i.balance
From Inserted i
Go

--
Alter Trigger OpenCreditActivity
On Credit After Insert
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 3, i.client_id, i.credit_id, GETDATE(), i.balance
From Inserted i
Go

--
Alter Trigger PayForCreditActivity
On Credit After Update
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 2, i.client_id, i.credit_id, GETDATE(), i.balance
From Inserted i
Go

Execute PayForCredit 'testnumber', 'test_number', '0000';
Go

--
Create Trigger CreateAccountActivity
On Account After Insert
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 5, i.client_id, i.account_id, GETDATE(), i.deposit
From Inserted i
Go

--
Create Trigger AddAccountActivity
On Account After Update
As
Insert Into Activity(type_id, client_id, moneybox_id, date, sum)
Select 6, i.client_id, i.account_id, GETDATE(), i.deposit
From Inserted i
Go

--10
Alter Procedure GetDebtors
As
With DebtInfo (credit_id, client_id, debt, monthsCount)
As
(Select Credit.credit_id, 
				Credit.client_id, 
				Credit.payment * DATEDIFF(m, next_payment, GETDATE()), 
				DATEDIFF(m, next_payment, GETDATE()) 
From Credit)

Select Client.client_id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)) As FIO, SUM(DebtInfo.debt) From Client
Join DebtInfo On DebtInfo.client_id = Client.client_id
Where Exists (Select * From DebtInfo Where monthsCount > 0 And DebtInfo.client_id = Client.client_id)
Group By Client.client_id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1))
Go

Execute GetDebtors;
Go

--
Create Procedure GetClientDebt
	@ClientId As int
As
Select credit_id, balance, payment, next_payment, closing_date, 
			 Credit.payment * DATEDIFF(m, next_payment, GETDATE()) As debt, 
			 DATEDIFF(m, next_payment, GETDATE()) As period_of_time 
From Credit
Where client_id = @ClientId 
	And DATEDIFF(m, next_payment, GETDATE()) > 0;
Go

Execute GetClientDebt 36;
Go

Execute MoveMoneyFromCardToCard 'test_number', '0000', 'test_number2', 40000;
Execute PayForCredit 'testnumber', 'test_number2', '0000';
Go

--10
Alter Procedure UpdateAccountAccumulation
As
Update Account Set accumulation += deposit * Tarif.rate
From
	(Select A.account_id, rate / 100 As rate From Account A
	 Join Deposit_tarif On A.deposit_tarif_id = Deposit_tarif.deposit_tarif_id
	 Where Exists (Select * From Account A_ex Where A_ex.closing_date > GETDATE() And A.account_id = A_ex.account_id)) As Tarif
Where Account.account_id = Tarif.account_id;

Execute UpdateAccountAccumulation;
Go

Insert Into Extra_money_source (type, sum) Values ('СамИнвест', 1000000);
Insert Into Extra_money_source (type, sum) Values ('Сбер', 500000);
Go

Alter Procedure MakeInvestIntoBank
	@CardNumber As varchar(19), @CardPinCode As varchar(4), @SourceId As int, @Sum As int
As
If  @CardPinCode = (Select pin_code From Card 
										Join Card_secret_data On Card.secret_data_id = Card_secret_data.secret_data_id 
										Where Card.number = @CardNumber)
		And @Sum < (Select balance From Card Where Card.number = @CardNumber)
		And @Sum < (Select sum From Extra_money_source Where source_id = @SourceId)
Begin
	Exec WithdrawMoneyFromCard @CardNumber, @CardPinCode, @Sum;
	Declare @ClientId As int;
	Set @ClientId = (Select client_id From Card Where number = @CardNumber)
	Declare @SourceSum As int;
	Set @SourceSum = (Select sum From Extra_money_source Where source_id = @SourceId)
	Insert Into SelfInvest (source_id, client_id, sum, source_sum) Values (
		@SourceId, @ClientId, @Sum, @SourceSum + @Sum);
	Update Extra_money_source Set sum += @Sum Where source_id = @SourceId;
End
Go

Execute TopUpCardBalance 'test_number', 100000;
Execute MakeInvestIntoBank 'test_number', '0000', 1, 50000;
Go

Select * From Extra_money_source;
Go

--11
--Вывести клиентов, у которых нет ни вкладов, ни кредитов
(Select Client.client_id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)) From Client)
Except
(Select Client.client_id As id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)) As name From Client
Join Credit On Credit.client_id = Client.client_id
Group By Client.client_id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1))
Union
Select Client.client_id As id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)) As name From Client
Join Account On Account.client_id = Client.client_id
Group By Client.client_id, CONCAT(Client.sername, ' ', Left(Client.name, 1), '.' ,Left(Client.father_name, 1)))
Go

--12
Alter Procedure AnalyzeBankProfitabilityForPeriod
	@Period As int
As
With Operation (moneybox_id, date)
As
(Select Activity.moneybox_id, Max(Activity.date) date From Activity_type, Activity
Where Exists (Select * From Activity A2 Where A2.type_id = Activity_type.type_id 
	And A2.activity_id = Activity.activity_id
	And DATEDIFF(m, GETDATE(), Activity.date) < @Period)
Group By Activity.moneybox_id)
Select Activity_type.name, Sum(Activity.sum) balance From Activity
Join Operation On Operation.moneybox_id = Activity.moneybox_id And Operation.date = Activity.date
Join Activity_type On Activity.type_id = Activity_type.type_id
Group By Activity_type.type_id, Activity_type.name
Go

Execute AnalyzeBankProfitabilityForPeriod 1;
Go

--13
Alter Procedure GetHistory
	@ActivityType As int, @MoneyBoxNumber As varchar(19), @Period As int
As
Declare @MonyboxId As int;
if (@ActivityType = 1)
	Set @MonyboxId = (Select Card.card_id From Card Where number = @MoneyBoxNumber);
if (@ActivityType = 2) Or (@ActivityType = 3)
	Set @MonyboxId = (Select Credit.credit_id From Credit Where number = @MoneyBoxNumber);
if (@ActivityType = 5) Or (@ActivityType = 6)
	Set @MonyboxId = (Select Account.account_id From Account Where number = @MoneyBoxNumber);
Select @MoneyBoxNumber, Activity.date, Activity.sum From Activity
Join Activity_type On Activity.type_id = Activity_type.type_id
Where Activity.moneybox_id = @MonyboxId
	And DATEDIFF(m, GETDATE(), Activity.date) < @Period;
Go

Execute GetHistory 1, '3221685761892795', 12;
Go

Alter Procedure GetActiveCreditRequests
As
Select Credit_request.request_id, Request_status.name, Credit_request.employee_id, Client.client_id As Client_ID, Client.sername, Client.name, Pasport_data.series, Pasport_data.number, Credit_request.amount, Credit_request.average_salary, Credit_request.tarif_id, Credit_request.time From Credit_request 
Join Request_status On Credit_request.status_id = Request_status.status_id
Join Client On Credit_request.client_id = Client.client_id
Join Pasport_data On Client.pasport_data_id = Pasport_data.pasport_data_id
Where Request_status.status_id != 3
Go
Execute GetActiveCreditRequests;
Go

Create Procedure SetEmployeeToCreditRequest
	@EId As int, @RId As int
As
Update Credit_request Set employee_id = @EId Where request_id = @RId
Go

Alter Procedure GetClientFullInfo
	@ClientId As int
As
(Select name, sername, father_name, series, number, birthday, phone_number From Client
Join Pasport_data On Pasport_data.pasport_data_id = Client.pasport_data_id
Where client_id = @ClientId)
Go

Execute GetClientFullInfo 36;
Go

Alter Procedure GetClientFinanceData
	@ClientId As int
As
(Select 'Кредит', number, Credit.balance, Credit.payment, closing_date, null From Credit)
Union
(Select 'Карта', number, balance, null, null, null From Card
Where client_id = @ClientId)
Union 
(Select 'Вклад', number, deposit, null, closing_date, accumulation From Account
Where client_id = @ClientId)
Go

Execute GetClientFinanceData 36;
GO

Create Procedure GetClientActivity
	@ClientId As int
As
Select Activity.date, name, Activity.sum From Activity
Join Activity_type On Activity.type_id = Activity_type.type_id
Where Activity.client_id = @ClientId

Alter Procedure CreateInvestOutRequest
	@ClientId As int
As
Insert Into WithdrawInvestRequest (client_id, status_id) Values (@ClientId, 1);
Go

Alter Procedure GetActiveInvestOutRequests
As
Select  WithdrawInvestRequest.request_id, Request_status.name status, WithdrawInvestRequest.client_id, WithdrawInvestRequest.invest_id, WithdrawInvestRequest.employee_id From WithdrawInvestRequest
Join Request_status On WithdrawInvestRequest.status_id = Request_status.status_id
Where WithdrawInvestRequest.status_id != 3
Go

Alter Procedure SetEmployeeInvestOutRequest
	@EmployeeId As int, @RequestId As int
As
Update WithdrawInvestRequest Set employee_id = @EmployeeId, status_id = 2 Where request_id = @RequestId
Go

Create Procedure CloseInvestOutRequest
	@RequestId As int, @InvestId As int
As
Update WithdrawInvestRequest Set invest_id = @InvestId, status_id = 3 Where request_id = @RequestId
Go

Alter Procedure GetClientIvests
	@ClientId As int
As
Select SelfInvest.invest_id, SelfInvest.source_id, Extra_money_source.type, SelfInvest.sum, source_sum, Extra_money_source.sum current_sum  From SelfInvest
Join Extra_money_source On Extra_money_source.source_id = SelfInvest.source_id
Where client_id = @ClientId;
Go

Create Procedure GetInvestInfoForComputing
	@InvestId As int
As
Select SelfInvest.sum , source_sum, Extra_money_source.sum current_sum From SelfInvest
Join Extra_money_source On Extra_money_source.source_id = SelfInvest.source_id
Where invest_id = @InvestId;
Go

Alter Procedure AppointEmployeeExtraSalary
	@EmployeeId As int, @ExtraSum As int
As
Update Employee Set extra_salary = @ExtraSum Where employee_id = @EmployeeId;
Select surname, Employee.name, father_name, Position.name, Position.salary, extra_salary From Employee 
Join Position On Employee.position_id = Position.position_id
Where employee_id = @EmployeeId;
Go

Execute AppointEmployeeExtraSalary 1, 2000;
Go