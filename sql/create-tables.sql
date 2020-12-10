USE [Sber]
GO
/****** Object:  Table [dbo].[Account]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Account](
	[account_id] [int] IDENTITY(1,1) NOT NULL,
	[client_id] [int] NOT NULL,
	[deposit_tarif_id] [int] NOT NULL,
	[number] [varchar](16) NOT NULL,
	[closing_date] [date] NOT NULL,
	[deposit] [float] NOT NULL,
	[accumulation] [float] NULL,
 CONSTRAINT [PK_Account] PRIMARY KEY CLUSTERED 
(
	[account_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Activity]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Activity](
	[activity_id] [int] IDENTITY(1,1) NOT NULL,
	[type_id] [int] NOT NULL,
	[client_id] [int] NOT NULL,
	[moneybox_id] [int] NULL,
	[date] [datetime2](3) NULL,
	[sum] [int] NULL,
 CONSTRAINT [PK_Activity_type_1] PRIMARY KEY CLUSTERED 
(
	[activity_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Activity_type]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Activity_type](
	[type_id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](30) NOT NULL,
 CONSTRAINT [PK_Activity_type] PRIMARY KEY CLUSTERED 
(
	[type_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Card]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Card](
	[card_id] [int] IDENTITY(1,1) NOT NULL,
	[client_id] [int] NOT NULL,
	[number] [varchar](19) NOT NULL,
	[secret_data_id] [int] NOT NULL,
	[validity] [varchar](5) NOT NULL,
	[balance] [float] NULL,
 CONSTRAINT [PK_Card] PRIMARY KEY CLUSTERED 
(
	[card_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Card_secret_data]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Card_secret_data](
	[secret_data_id] [int] IDENTITY(1,1) NOT NULL,
	[cvv_code] [varchar](3) NOT NULL,
	[pin_code] [varchar](4) NOT NULL,
 CONSTRAINT [PK_Card_secret_data] PRIMARY KEY CLUSTERED 
(
	[secret_data_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Client]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Client](
	[client_id] [int] IDENTITY(1,1) NOT NULL,
	[pasport_data_id] [int] NOT NULL,
	[name] [varchar](50) NOT NULL,
	[sername] [varchar](50) NOT NULL,
	[father_name] [varchar](50) NULL,
	[birthday] [date] NULL,
	[phone_number] [varchar](11) NULL,
 CONSTRAINT [PK_Client] PRIMARY KEY CLUSTERED 
(
	[client_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Credit]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Credit](
	[credit_id] [int] IDENTITY(1,1) NOT NULL,
	[number] [varchar](10) NOT NULL,
	[client_id] [int] NOT NULL,
	[credit_tarif_id] [int] NOT NULL,
	[payment] [float] NOT NULL,
	[balance] [float] NOT NULL,
	[next_payment] [date] NOT NULL,
	[closing_date] [date] NOT NULL,
 CONSTRAINT [PK_Credit] PRIMARY KEY CLUSTERED 
(
	[credit_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Credit_request]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Credit_request](
	[request_id] [int] IDENTITY(1,1) NOT NULL,
	[client_id] [int] NOT NULL,
	[average_salary] [int] NOT NULL,
	[amount] [float] NOT NULL,
	[employee_id] [int] NULL,
	[tarif_id] [int] NULL,
	[time] [int] NULL,
	[status_id] [int] NOT NULL,
 CONSTRAINT [PK_Credit_request] PRIMARY KEY CLUSTERED 
(
	[request_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Credit_tarif]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Credit_tarif](
	[credit_tarif_id] [int] IDENTITY(1,1) NOT NULL,
	[rate] [float] NOT NULL,
	[max_credit] [float] NOT NULL,
 CONSTRAINT [PK_Credit_tarif] PRIMARY KEY CLUSTERED 
(
	[credit_tarif_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Deposit_tarif]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Deposit_tarif](
	[deposit_tarif_id] [int] IDENTITY(1,1) NOT NULL,
	[rate] [float] NOT NULL,
	[min_deposit] [int] NOT NULL,
 CONSTRAINT [PK_Deposit_tarif] PRIMARY KEY CLUSTERED 
(
	[deposit_tarif_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employee]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employee](
	[employee_id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](50) NOT NULL,
	[surname] [varchar](50) NOT NULL,
	[father_name] [varchar](50) NULL,
	[login_data_id] [int] NOT NULL,
	[position_id] [int] NOT NULL,
	[extra_salary] [int] NULL,
 CONSTRAINT [PK_Employee] PRIMARY KEY CLUSTERED 
(
	[employee_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employee_activity]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employee_activity](
	[employee_activity_id] [int] IDENTITY(1,1) NOT NULL,
	[employee_id] [int] NOT NULL,
	[activity_id] [int] NOT NULL,
 CONSTRAINT [PK_Employee_activity] PRIMARY KEY CLUSTERED 
(
	[employee_activity_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employee_login_data]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employee_login_data](
	[login_data_id] [int] IDENTITY(1,1) NOT NULL,
	[username] [varchar](50) NOT NULL,
	[password] [varchar](50) NOT NULL,
 CONSTRAINT [PK_Employee_login_data] PRIMARY KEY CLUSTERED 
(
	[login_data_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Extra_money_source]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Extra_money_source](
	[source_id] [int] IDENTITY(1,1) NOT NULL,
	[type] [varchar](50) NOT NULL,
	[sum] [float] NOT NULL,
 CONSTRAINT [PK_Extra_money_source] PRIMARY KEY CLUSTERED 
(
	[source_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Pasport_data]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Pasport_data](
	[pasport_data_id] [int] IDENTITY(1,1) NOT NULL,
	[number] [int] NOT NULL,
	[series] [int] NOT NULL,
 CONSTRAINT [PK_Pasport_data] PRIMARY KEY CLUSTERED 
(
	[pasport_data_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Position]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Position](
	[position_id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](30) NOT NULL,
	[salary] [int] NOT NULL,
 CONSTRAINT [PK_Position] PRIMARY KEY CLUSTERED 
(
	[position_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Request_status]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Request_status](
	[status_id] [int] IDENTITY(1,1) NOT NULL,
	[name] [varchar](30) NOT NULL,
 CONSTRAINT [PK_Request_status] PRIMARY KEY CLUSTERED 
(
	[status_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[SelfInvest]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[SelfInvest](
	[invest_id] [int] IDENTITY(1,1) NOT NULL,
	[source_id] [int] NOT NULL,
	[client_id] [int] NOT NULL,
	[sum] [int] NOT NULL,
	[source_sum] [int] NULL,
 CONSTRAINT [PK_SelfInvest] PRIMARY KEY CLUSTERED 
(
	[invest_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[WithdrawInvestRequest]    Script Date: 10.12.2020 16:42:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[WithdrawInvestRequest](
	[request_id] [int] IDENTITY(1,1) NOT NULL,
	[client_id] [int] NOT NULL,
	[invest_id] [int] NULL,
	[status_id] [int] NOT NULL,
	[employee_id] [int] NULL,
 CONSTRAINT [PK_WithdrawInvest] PRIMARY KEY CLUSTERED 
(
	[request_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Credit_request] ADD  CONSTRAINT [DF_Credit_request_status]  DEFAULT ('opened') FOR [status_id]
GO
ALTER TABLE [dbo].[Account]  WITH CHECK ADD  CONSTRAINT [FK_Account_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[Account] CHECK CONSTRAINT [FK_Account_Client]
GO
ALTER TABLE [dbo].[Account]  WITH CHECK ADD  CONSTRAINT [FK_Account_Deposit_tarif] FOREIGN KEY([deposit_tarif_id])
REFERENCES [dbo].[Deposit_tarif] ([deposit_tarif_id])
GO
ALTER TABLE [dbo].[Account] CHECK CONSTRAINT [FK_Account_Deposit_tarif]
GO
ALTER TABLE [dbo].[Activity]  WITH CHECK ADD  CONSTRAINT [FK_Activity_Activity_type] FOREIGN KEY([type_id])
REFERENCES [dbo].[Activity_type] ([type_id])
GO
ALTER TABLE [dbo].[Activity] CHECK CONSTRAINT [FK_Activity_Activity_type]
GO
ALTER TABLE [dbo].[Activity]  WITH CHECK ADD  CONSTRAINT [FK_Activity_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[Activity] CHECK CONSTRAINT [FK_Activity_Client]
GO
ALTER TABLE [dbo].[Card]  WITH CHECK ADD  CONSTRAINT [FK_Card_Card_secret_data] FOREIGN KEY([secret_data_id])
REFERENCES [dbo].[Card_secret_data] ([secret_data_id])
GO
ALTER TABLE [dbo].[Card] CHECK CONSTRAINT [FK_Card_Card_secret_data]
GO
ALTER TABLE [dbo].[Card]  WITH CHECK ADD  CONSTRAINT [FK_Card_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[Card] CHECK CONSTRAINT [FK_Card_Client]
GO
ALTER TABLE [dbo].[Client]  WITH CHECK ADD  CONSTRAINT [FK_Client_Pasport_data] FOREIGN KEY([pasport_data_id])
REFERENCES [dbo].[Pasport_data] ([pasport_data_id])
GO
ALTER TABLE [dbo].[Client] CHECK CONSTRAINT [FK_Client_Pasport_data]
GO
ALTER TABLE [dbo].[Credit]  WITH CHECK ADD  CONSTRAINT [FK_Credit_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[Credit] CHECK CONSTRAINT [FK_Credit_Client]
GO
ALTER TABLE [dbo].[Credit]  WITH CHECK ADD  CONSTRAINT [FK_Credit_Credit_tarif] FOREIGN KEY([credit_tarif_id])
REFERENCES [dbo].[Credit_tarif] ([credit_tarif_id])
GO
ALTER TABLE [dbo].[Credit] CHECK CONSTRAINT [FK_Credit_Credit_tarif]
GO
ALTER TABLE [dbo].[Credit_request]  WITH CHECK ADD  CONSTRAINT [FK_Credit_request_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[Credit_request] CHECK CONSTRAINT [FK_Credit_request_Client]
GO
ALTER TABLE [dbo].[Credit_request]  WITH CHECK ADD  CONSTRAINT [FK_Credit_request_Credit_tarif] FOREIGN KEY([tarif_id])
REFERENCES [dbo].[Credit_tarif] ([credit_tarif_id])
GO
ALTER TABLE [dbo].[Credit_request] CHECK CONSTRAINT [FK_Credit_request_Credit_tarif]
GO
ALTER TABLE [dbo].[Credit_request]  WITH CHECK ADD  CONSTRAINT [FK_Credit_request_Employee] FOREIGN KEY([employee_id])
REFERENCES [dbo].[Employee] ([employee_id])
GO
ALTER TABLE [dbo].[Credit_request] CHECK CONSTRAINT [FK_Credit_request_Employee]
GO
ALTER TABLE [dbo].[Credit_request]  WITH CHECK ADD  CONSTRAINT [FK_Credit_request_Request_status] FOREIGN KEY([status_id])
REFERENCES [dbo].[Request_status] ([status_id])
GO
ALTER TABLE [dbo].[Credit_request] CHECK CONSTRAINT [FK_Credit_request_Request_status]
GO
ALTER TABLE [dbo].[Employee]  WITH CHECK ADD  CONSTRAINT [FK_Employee_Employee_login_data] FOREIGN KEY([login_data_id])
REFERENCES [dbo].[Employee_login_data] ([login_data_id])
GO
ALTER TABLE [dbo].[Employee] CHECK CONSTRAINT [FK_Employee_Employee_login_data]
GO
ALTER TABLE [dbo].[Employee]  WITH CHECK ADD  CONSTRAINT [FK_Employee_Position] FOREIGN KEY([position_id])
REFERENCES [dbo].[Position] ([position_id])
GO
ALTER TABLE [dbo].[Employee] CHECK CONSTRAINT [FK_Employee_Position]
GO
ALTER TABLE [dbo].[Employee_activity]  WITH CHECK ADD  CONSTRAINT [FK_Employee_activity_Activity] FOREIGN KEY([activity_id])
REFERENCES [dbo].[Activity] ([activity_id])
GO
ALTER TABLE [dbo].[Employee_activity] CHECK CONSTRAINT [FK_Employee_activity_Activity]
GO
ALTER TABLE [dbo].[Employee_activity]  WITH CHECK ADD  CONSTRAINT [FK_Employee_activity_Employee] FOREIGN KEY([employee_id])
REFERENCES [dbo].[Employee] ([employee_id])
GO
ALTER TABLE [dbo].[Employee_activity] CHECK CONSTRAINT [FK_Employee_activity_Employee]
GO
ALTER TABLE [dbo].[SelfInvest]  WITH CHECK ADD  CONSTRAINT [FK_SelfInvest_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[SelfInvest] CHECK CONSTRAINT [FK_SelfInvest_Client]
GO
ALTER TABLE [dbo].[SelfInvest]  WITH CHECK ADD  CONSTRAINT [FK_SelfInvest_Extra_money_source] FOREIGN KEY([source_id])
REFERENCES [dbo].[Extra_money_source] ([source_id])
GO
ALTER TABLE [dbo].[SelfInvest] CHECK CONSTRAINT [FK_SelfInvest_Extra_money_source]
GO
ALTER TABLE [dbo].[WithdrawInvestRequest]  WITH CHECK ADD  CONSTRAINT [FK_WithdrawInvestRequest_Client] FOREIGN KEY([client_id])
REFERENCES [dbo].[Client] ([client_id])
GO
ALTER TABLE [dbo].[WithdrawInvestRequest] CHECK CONSTRAINT [FK_WithdrawInvestRequest_Client]
GO
ALTER TABLE [dbo].[WithdrawInvestRequest]  WITH CHECK ADD  CONSTRAINT [FK_WithdrawInvestRequest_Employee] FOREIGN KEY([employee_id])
REFERENCES [dbo].[Employee] ([employee_id])
GO
ALTER TABLE [dbo].[WithdrawInvestRequest] CHECK CONSTRAINT [FK_WithdrawInvestRequest_Employee]
GO
ALTER TABLE [dbo].[WithdrawInvestRequest]  WITH CHECK ADD  CONSTRAINT [FK_WithdrawInvestRequest_Request_status] FOREIGN KEY([status_id])
REFERENCES [dbo].[Request_status] ([status_id])
GO
ALTER TABLE [dbo].[WithdrawInvestRequest] CHECK CONSTRAINT [FK_WithdrawInvestRequest_Request_status]
GO
ALTER TABLE [dbo].[WithdrawInvestRequest]  WITH CHECK ADD  CONSTRAINT [FK_WithdrawInvestRequest_SelfInvest] FOREIGN KEY([invest_id])
REFERENCES [dbo].[SelfInvest] ([invest_id])
GO
ALTER TABLE [dbo].[WithdrawInvestRequest] CHECK CONSTRAINT [FK_WithdrawInvestRequest_SelfInvest]
GO
