## 合并单元格

```vba
Sub MergedCells()
    '从下向上合并
    Dim myRange As Variant
    Dim arr As Variant
    Dim i, j, cmax, rmax, str, a
    Dim rng As Range

    Excel.Application.DisplayAlerts = False    '关闭合并单元格时弹出的仅保留左上角值的弹窗
    '选择需要合并的区域，如果是多个不连续的区域，按住ctrl进行选择即可
    Set myRange = Application.InputBox(prompt:="Select a cell to be expanded", Type:=8)
    'Address属性返回的是单元格区域的绝对引用，如果是多个不连续区域，是用英文逗号隔开
    arr = Split(myRange.Address, ",")

    For Each a In arr   '遍历选中的每一个不连续的区域，如果是连续区域，那就只有一个
        Set rng = Range(Replace(a, "$", ""))
        '此处括号内得到的已经是字符串格式了，再使用range做引用即可，无需再对括号内的内容进行左右的双引号连接
        '如果有需要把双引号作为连接内容的场景，可以加双重引号，比如"""excel"""，得到的就是"excel"；'也可以直接使用chr(34)进行连接，它对应的就是双引号
        rmax = rng.Rows.Count
        cmax = rng.Columns.Count

        For j = 1 To cmax
            For i = rmax To 2 Step -1  '遍历区域的行到第2行，默认存在标题行
            '从下向上合并，到第2行时，其内容不会和标题行一样，所以不合并，从上向下合并代码量较多
                If rng.Cells(i, j).Value = rng.Cells(i - 1, j).Value Then
                    With Range(rng.Cells(i - 1, j), rng.Cells(i, j))
                        .Merge
                        .HorizontalAlignment = xlCenter
                        .VerticalAlignment = xlCenter
                    End With
                End If
            Next
        Next

    Next
    Excel.Application.DisplayAlerts = True
End Sub
```

## 取消单元格合并并填充

```vba
Sub SplitMergedCellsAndFill()
    Dim myRange As Variant
    Dim arr As Variant
    Dim rng As Range
    Dim cell As Range
    Dim i As Long
    Dim a As Variant

    ' Turn off alerts for unmerging cells
    Excel.Application.DisplayAlerts = False

    ' Prompt the user to select a range of cells to unmerge and fill
    Set myRange = Application.InputBox(prompt:="Select a cell to be expanded", Type:=8)

    ' Split the selected ranges in case of multiple non-contiguous selections
    arr = Split(myRange.Address, ",")

    ' Loop through each selected range
    For Each a In arr
        Set rng = Range(Replace(a, "$", ""))

        ' Loop through each cell in the selected range
        For Each cell In rng
            ' Check if the cell is part of a merged cell
            If cell.MergeCells Then
                ' Get the number of rows in the merged cell area
                Dim rowCount As Long
                rowCount = cell.MergeArea.Rows.Count

                ' Unmerge the cells
                cell.MergeArea.UnMerge

                ' Fill the unmerged cells with the value from the first cell
                For i = 2 To rowCount
                    With cell.Offset(i - 1, 0)
                        .Value = cell.Value
                        .HorizontalAlignment = xlCenter
                        .VerticalAlignment = xlCenter
                    End With
                Next i

                ' Set alignment for the original cell
                With cell
                    .HorizontalAlignment = xlCenter
                    .VerticalAlignment = xlCenter
                End With
            End If
        Next cell
    Next

    ' Turn alerts back on
    Excel.Application.DisplayAlerts = True
End Sub
```
