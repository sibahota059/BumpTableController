//
//  BumpTableModel.h
//  Flock
//
//  Created by Sahil Desai on 12/11/12.
//  Copyright (c) 2012 Bump Technologies Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BumpTableSection;
@class BumpTableRow;


/*!
 @class BumpTableModel

 @abstract
 The `BumpTableModel` object is the model backing for a BumpTableView

 @discussion

 */
@interface BumpTableModel : NSObject

/*!
 @abstract
 The table section objects that make up the model
 
 @discussion
 This should only contain `BumpTableSection` objects
 */
@property (nonatomic, copy) NSArray *sections;

/*!
 @abstract
 Array containing the selected table rows
 */
@property (readonly) NSArray *selectedRows;

/*!
 @abstract
 Creates and returns an model object configured with the sections provided

 @param sections    Array of `BumpTableSection` objects
 */
+ (instancetype)modelWithSections:(NSArray *)sections;

/*!
 @abstract
 Creates and returns an model object configured with the rows provided 
 inside of a single section with the key "all"

 @param rows        Array of `BumpTableRow` objects
 */
+ (instancetype)modelWithRows:(NSArray *)rows;

/*!
 @abstract
 Returns a dictionary containing the `NSIndexPath` of each section keyed on their unique keys
 */
- (NSDictionary *)sectionIndexes;

/*!
 @abstract
 Returns a dictionary containing the `NSIndexPath` of each row, keyed on their unique keys
 */
- (NSDictionary *)rowIndexPaths;

/*!
 @abstract
 Returns an array that contains each table-row, resulting from a filter of all
 rows in the current model using the given string

 @param searchString    The string to use to filter
 */
- (NSMutableArray *)rowsForSearchString:(NSString *)searchString;

/*!
 @abstract
 Same as rowsForSearchString, except the resulting filtered rows are wrapped 
 in a `BumpTableModel` and returned

 @param searchString    The string to use to filter
 */
- (BumpTableModel *)modelForSearchString:(NSString *)searchString;

/*!
 @abstract
 Returns the `NSIndexPath` for a given row. Will return nil if row does not exist in this table

 @param row     A table row that exists in this model
 */
- (NSIndexPath *)indexPathForRow:(BumpTableRow *)row;

@end


/*!
 @typedef BumpTableHeaderFooterGenerator

 @abstract
 Block used to create and return a UIView to be used as a table header or footer
 */
typedef UIView *(^BumpTableHeaderFooterGenerator)(void);

/*!
 @class BmpTableHeaderFooter

 @abstract
 Model for a table header or footer
 */
@interface BumpTableHeaderFooter : NSObject

/*!
 @abstract
 the height of the header or footer
 */
@property (nonatomic) CGFloat height;

/*!
 @abstract
 The generator that it used to create the table header or footer
 */
@property (nonatomic, copy) BumpTableHeaderFooterGenerator generator;

/*!
 @abstract
 Creates and returns a headerFooter model object, to be set on a table model

 @param height      The height of the header or footer view
 @param generator   The block used to create the header or footer view
 */
+ (instancetype)headerFooterForHeight:(CGFloat)height generator:(BumpTableHeaderFooterGenerator)generator;

@end


/*!
 @class BumpTableSection

 @abstract

 @discussion

 */
@interface BumpTableSection : NSObject

/*!
 @abstract
 Must be unique in a table, specific within section. Used to animate transitions
 */
@property (nonatomic, strong) NSObject <NSCopying> *key;

/*!
 @abstract
 Array of table row objects contained in this section
 */
@property (nonatomic, strong) NSArray *rows;

/*!
 @abstract
 The index title to use if the table has scrubber enabled
 */
@property (nonatomic, strong) NSString *indexTitle;

/*!
 @abstract
 Header model for table
 */
@property (nonatomic, strong) BumpTableHeaderFooter *header;

/*!
 @abstract
 Footer model for table
 */
@property (nonatomic, strong) BumpTableHeaderFooter *footer;

/*!
 @abstract
 Creates and returns a table section with the given key and rows

 @param key     A unique key used to identify this section
 @param rows    The rows that should be in this section (cannot be nil)
 */
+ (instancetype)sectionWithKey:(NSObject<NSCopying>*)key rows:(NSArray*)rows;

@end


/*!
 @typedef BumpTableHeaderFooterUpdater

 @abstract

 @discussion

 */
typedef UITableViewCell *(^BumpTableCellGenerator)(NSString *reuseIdentifier);

/*!
 @typedef BumpTableHeaderFooterUpdater

 @abstract

 @discussion

 */
typedef void (^BumpTableCellUpdater)(id cell);

/*!
 @typedef BumpTableHeaderFooterUpdater

 @abstract

 @discussion

 */
typedef void (^BumpTableCellOnSelection)(id cell);

/*!
 @typedef BumpTableHeaderFooterUpdater

 @abstract

 @discussion

 */
typedef void (^BumpTableCellOnSwipeConfirmation)(id cell);

/*!
 @class

 @abstract

 @discussion

 */
@interface BumpTableRow : NSObject
// Must be unique in a table, specific to the data of one row. Used to animate transitions
@property (nonatomic, strong) NSObject <NSCopying> *key;
// String to be used for searching
@property (nonatomic, strong) NSString *searchString;
// The height of the cell, needed by UITableView for upfront calculation
@property (nonatomic) CGFloat height;
// Identifies the cell for use by other similar rows
@property (nonatomic, strong) NSString *reuseIdentifier;
// Indicates whether this row is selectable
@property (nonatomic) BOOL selectable;
// Indicates whether this row is selectable. Defaults to yes.
@property (nonatomic) BOOL selected;

/* if a cell of the designated reuseId can't be produced by recycling old ones,
 * this will generate a new one. Note: this may not be called for all rows,
 * and the cell returned may be recycled for other rows */
@property (nonatomic, copy) BumpTableCellGenerator generator;
/* This is called to customize the cell for this particular row.
 * This will be called upon creation of a new cell, when the cell recycles,
 * and when the model changes (if cell is visible) */
@property (nonatomic, copy) BumpTableCellUpdater customizer;

//This get's called when the user taps on a row.
//It should be used if you don't care about selection state callbacks below
@property (nonatomic, copy) BumpTableCellOnSelection onTap;

// This gets called when the row is selected
@property (nonatomic, copy) BumpTableCellOnSelection onSelection;
// This gets called when the row is deselected
@property (nonatomic, copy) BumpTableCellOnSelection onDeselection;
// This gets called when the row's swipe confirmation button is pressed
@property (nonatomic, copy) BumpTableCellOnSwipeConfirmation onSwipeConfirmation;

/*!
 @abstract

 @param
 @param
 @param
 @param 
 */
+ (instancetype)rowWithKey:(NSObject*)key
                    height:(CGFloat)height
           reuseIdentifier:(NSString *)reuseIdentifier
                 generator:(BumpTableCellGenerator)generator;
@end